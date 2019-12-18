#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_vgpu_gtt {TYPE_2__* ggtt_mm; int /*<<< orphan*/  post_shadow_list_head; int /*<<< orphan*/  oos_page_list_head; int /*<<< orphan*/  ppgtt_mm_list_head; int /*<<< orphan*/  spt_tree; } ;
struct intel_vgpu {struct intel_vgpu_gtt gtt; } ;
struct TYPE_5__ {int /*<<< orphan*/  partial_pte_list; } ;
struct TYPE_6__ {TYPE_1__ ggtt_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int create_scratch_page_tree (struct intel_vgpu*) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 TYPE_2__* intel_vgpu_create_ggtt_mm (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_reset_ggtt (struct intel_vgpu*,int) ; 

int intel_vgpu_init_gtt(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_gtt *gtt = &vgpu->gtt;

	INIT_RADIX_TREE(&gtt->spt_tree, GFP_KERNEL);

	INIT_LIST_HEAD(&gtt->ppgtt_mm_list_head);
	INIT_LIST_HEAD(&gtt->oos_page_list_head);
	INIT_LIST_HEAD(&gtt->post_shadow_list_head);

	gtt->ggtt_mm = intel_vgpu_create_ggtt_mm(vgpu);
	if (IS_ERR(gtt->ggtt_mm)) {
		gvt_vgpu_err("fail to create mm for ggtt.\n");
		return PTR_ERR(gtt->ggtt_mm);
	}

	intel_vgpu_reset_ggtt(vgpu, false);

	INIT_LIST_HEAD(&gtt->ggtt_mm->ggtt_mm.partial_pte_list);

	return create_scratch_page_tree(vgpu);
}