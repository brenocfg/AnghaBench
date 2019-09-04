#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  clear_pages; int /*<<< orphan*/  set_pages; int /*<<< orphan*/  unbind_vma; int /*<<< orphan*/  bind_vma; } ;
struct TYPE_11__ {int total; int /*<<< orphan*/  pte_encode; TYPE_3__ vma_ops; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  insert_entries; int /*<<< orphan*/  clear_range; int /*<<< orphan*/  allocate_va_range; int /*<<< orphan*/ * dma; struct drm_i915_private* i915; } ;
struct i915_hw_ppgtt {TYPE_5__ vm; int /*<<< orphan*/  debug_dump; int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {int /*<<< orphan*/  pte_encode; } ;
struct i915_ggtt {TYPE_4__ vm; } ;
struct gen6_hw_ppgtt {struct i915_hw_ppgtt base; int /*<<< orphan*/  vma; } ;
struct TYPE_8__ {TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_2__ drm; struct i915_ggtt ggtt; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct i915_hw_ppgtt* ERR_PTR (int) ; 
 int /*<<< orphan*/  GEN6_PD_SIZE ; 
 int GEN6_PTES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I915_GTT_PAGE_SIZE ; 
 int I915_PDES ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_pages ; 
 int /*<<< orphan*/  gen6_alloc_va_range ; 
 int /*<<< orphan*/  gen6_dump_ppgtt ; 
 int /*<<< orphan*/  gen6_ppgtt_cleanup ; 
 int /*<<< orphan*/  gen6_ppgtt_clear_range ; 
 int /*<<< orphan*/  gen6_ppgtt_free_scratch (TYPE_5__*) ; 
 int gen6_ppgtt_init_scratch (struct gen6_hw_ppgtt*) ; 
 int /*<<< orphan*/  gen6_ppgtt_insert_entries ; 
 int /*<<< orphan*/  i915_address_space_init (TYPE_5__*,struct drm_i915_private*) ; 
 int /*<<< orphan*/  kfree (struct gen6_hw_ppgtt*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gen6_hw_ppgtt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_vma_create (struct gen6_hw_ppgtt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppgtt_bind_vma ; 
 int /*<<< orphan*/  ppgtt_set_pages ; 
 int /*<<< orphan*/  ppgtt_unbind_vma ; 

__attribute__((used)) static struct i915_hw_ppgtt *gen6_ppgtt_create(struct drm_i915_private *i915)
{
	struct i915_ggtt * const ggtt = &i915->ggtt;
	struct gen6_hw_ppgtt *ppgtt;
	int err;

	ppgtt = kzalloc(sizeof(*ppgtt), GFP_KERNEL);
	if (!ppgtt)
		return ERR_PTR(-ENOMEM);

	kref_init(&ppgtt->base.ref);

	ppgtt->base.vm.i915 = i915;
	ppgtt->base.vm.dma = &i915->drm.pdev->dev;

	ppgtt->base.vm.total = I915_PDES * GEN6_PTES * I915_GTT_PAGE_SIZE;

	i915_address_space_init(&ppgtt->base.vm, i915);

	ppgtt->base.vm.allocate_va_range = gen6_alloc_va_range;
	ppgtt->base.vm.clear_range = gen6_ppgtt_clear_range;
	ppgtt->base.vm.insert_entries = gen6_ppgtt_insert_entries;
	ppgtt->base.vm.cleanup = gen6_ppgtt_cleanup;
	ppgtt->base.debug_dump = gen6_dump_ppgtt;

	ppgtt->base.vm.vma_ops.bind_vma    = ppgtt_bind_vma;
	ppgtt->base.vm.vma_ops.unbind_vma  = ppgtt_unbind_vma;
	ppgtt->base.vm.vma_ops.set_pages   = ppgtt_set_pages;
	ppgtt->base.vm.vma_ops.clear_pages = clear_pages;

	ppgtt->base.vm.pte_encode = ggtt->vm.pte_encode;

	err = gen6_ppgtt_init_scratch(ppgtt);
	if (err)
		goto err_free;

	ppgtt->vma = pd_vma_create(ppgtt, GEN6_PD_SIZE);
	if (IS_ERR(ppgtt->vma)) {
		err = PTR_ERR(ppgtt->vma);
		goto err_scratch;
	}

	return &ppgtt->base;

err_scratch:
	gen6_ppgtt_free_scratch(&ppgtt->base.vm);
err_free:
	kfree(ppgtt);
	return ERR_PTR(err);
}