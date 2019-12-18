#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct intel_gt {TYPE_9__* i915; TYPE_2__* ggtt; } ;
struct TYPE_14__ {int offset; } ;
struct TYPE_15__ {TYPE_5__ partial; } ;
struct i915_vma {int /*<<< orphan*/  size; TYPE_6__ ggtt_view; TYPE_4__* obj; TYPE_1__* fence; } ;
struct drm_vma_offset_node {int dummy; } ;
struct TYPE_17__ {TYPE_7__* anon_inode; } ;
struct TYPE_18__ {TYPE_8__ drm; } ;
struct TYPE_16__ {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_12__ {struct drm_vma_offset_node vma_node; } ;
struct TYPE_13__ {TYPE_3__ base; } ;
struct TYPE_11__ {int num_fences; TYPE_1__* fence_regs; } ;
struct TYPE_10__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 struct i915_vma* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_vma_node_offset_addr (struct drm_vma_offset_node*) ; 
 int /*<<< orphan*/  i915_vma_has_userfault (struct i915_vma*) ; 
 int /*<<< orphan*/  unmap_mapping_range (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void revoke_mmaps(struct intel_gt *gt)
{
	int i;

	for (i = 0; i < gt->ggtt->num_fences; i++) {
		struct drm_vma_offset_node *node;
		struct i915_vma *vma;
		u64 vma_offset;

		vma = READ_ONCE(gt->ggtt->fence_regs[i].vma);
		if (!vma)
			continue;

		if (!i915_vma_has_userfault(vma))
			continue;

		GEM_BUG_ON(vma->fence != &gt->ggtt->fence_regs[i]);
		node = &vma->obj->base.vma_node;
		vma_offset = vma->ggtt_view.partial.offset << PAGE_SHIFT;
		unmap_mapping_range(gt->i915->drm.anon_inode->i_mapping,
				    drm_vma_node_offset_addr(node) + vma_offset,
				    vma->size,
				    1);
	}
}