#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct i915_vma {int size; int fence_size; TYPE_4__* vm; int /*<<< orphan*/  vm_link; int /*<<< orphan*/  obj_link; TYPE_3__ ggtt_view; int /*<<< orphan*/  flags; int /*<<< orphan*/  active; struct gen6_hw_ppgtt* private; int /*<<< orphan*/ * ops; int /*<<< orphan*/  last_fence; } ;
struct TYPE_8__ {int total; int /*<<< orphan*/  unbound_list; } ;
struct i915_ggtt {TYPE_4__ vm; } ;
struct TYPE_5__ {struct drm_i915_private* i915; } ;
struct TYPE_6__ {TYPE_1__ vm; } ;
struct gen6_hw_ppgtt {TYPE_2__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  vmas; struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_vma* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_GGTT_VIEW_ROTATED ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  I915_VMA_GGTT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  init_request_active (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct i915_vma* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_vma_ops ; 

__attribute__((used)) static struct i915_vma *pd_vma_create(struct gen6_hw_ppgtt *ppgtt, int size)
{
	struct drm_i915_private *i915 = ppgtt->base.vm.i915;
	struct i915_ggtt *ggtt = &i915->ggtt;
	struct i915_vma *vma;

	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(size > ggtt->vm.total);

	vma = kmem_cache_zalloc(i915->vmas, GFP_KERNEL);
	if (!vma)
		return ERR_PTR(-ENOMEM);

	init_request_active(&vma->last_fence, NULL);

	vma->vm = &ggtt->vm;
	vma->ops = &pd_vma_ops;
	vma->private = ppgtt;

	vma->active = RB_ROOT;

	vma->size = size;
	vma->fence_size = size;
	vma->flags = I915_VMA_GGTT;
	vma->ggtt_view.type = I915_GGTT_VIEW_ROTATED; /* prevent fencing */

	INIT_LIST_HEAD(&vma->obj_link);
	list_add(&vma->vm_link, &vma->vm->unbound_list);

	return vma;
}