#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
struct intel_vgpu_ppgtt_spt {TYPE_1__ shadow_page; struct intel_vgpu* vgpu; } ;
struct TYPE_10__ {TYPE_4__* scratch_pt; } ;
struct intel_vgpu {TYPE_5__ gtt; TYPE_3__* gvt; } ;
struct intel_gvt_gtt_pte_ops {int (* test_present ) (struct intel_gvt_gtt_entry*) ;int /*<<< orphan*/  (* set_pfn ) (struct intel_gvt_gtt_entry*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* clear_pse ) (struct intel_gvt_gtt_entry*) ;int /*<<< orphan*/  (* clear_64k_splited ) (struct intel_gvt_gtt_entry*) ;scalar_t__ (* test_64k_splited ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {scalar_t__ type; int /*<<< orphan*/  val64; } ;
struct TYPE_9__ {int /*<<< orphan*/  page_mfn; } ;
struct TYPE_7__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_8__ {TYPE_2__ gtt; } ;

/* Variables and functions */
 unsigned long GTT_64K_PTE_STRIDE ; 
 scalar_t__ GTT_TYPE_PPGTT_PTE_1G_ENTRY ; 
 scalar_t__ GTT_TYPE_PPGTT_PTE_2M_ENTRY ; 
 int /*<<< orphan*/  gvt_vdbg_mm (char*) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ppgtt_get_shadow_entry (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int ppgtt_handle_guest_entry_add (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int ppgtt_handle_guest_entry_removal (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  ppgtt_set_shadow_entry (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int stub1 (struct intel_gvt_gtt_entry*) ; 
 scalar_t__ stub2 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  stub3 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  stub4 (struct intel_gvt_gtt_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct intel_gvt_gtt_entry*) ; 
 int /*<<< orphan*/  stub6 (struct intel_gvt_gtt_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct intel_gvt_gtt_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppgtt_handle_guest_write_page_table(
		struct intel_vgpu_ppgtt_spt *spt,
		struct intel_gvt_gtt_entry *we, unsigned long index)
{
	struct intel_vgpu *vgpu = spt->vgpu;
	int type = spt->shadow_page.type;
	struct intel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	struct intel_gvt_gtt_entry old_se;
	int new_present;
	int i, ret;

	new_present = ops->test_present(we);

	/*
	 * Adding the new entry first and then removing the old one, that can
	 * guarantee the ppgtt table is validated during the window between
	 * adding and removal.
	 */
	ppgtt_get_shadow_entry(spt, &old_se, index);

	if (new_present) {
		ret = ppgtt_handle_guest_entry_add(spt, we, index);
		if (ret)
			goto fail;
	}

	ret = ppgtt_handle_guest_entry_removal(spt, &old_se, index);
	if (ret)
		goto fail;

	if (!new_present) {
		/* For 64KB splited entries, we need clear them all. */
		if (ops->test_64k_splited(&old_se) &&
		    !(index % GTT_64K_PTE_STRIDE)) {
			gvt_vdbg_mm("remove splited 64K shadow entries\n");
			for (i = 0; i < GTT_64K_PTE_STRIDE; i++) {
				ops->clear_64k_splited(&old_se);
				ops->set_pfn(&old_se,
					vgpu->gtt.scratch_pt[type].page_mfn);
				ppgtt_set_shadow_entry(spt, &old_se, index + i);
			}
		} else if (old_se.type == GTT_TYPE_PPGTT_PTE_2M_ENTRY ||
			   old_se.type == GTT_TYPE_PPGTT_PTE_1G_ENTRY) {
			ops->clear_pse(&old_se);
			ops->set_pfn(&old_se,
				     vgpu->gtt.scratch_pt[type].page_mfn);
			ppgtt_set_shadow_entry(spt, &old_se, index);
		} else {
			ops->set_pfn(&old_se,
				     vgpu->gtt.scratch_pt[type].page_mfn);
			ppgtt_set_shadow_entry(spt, &old_se, index);
		}
	}

	return 0;
fail:
	gvt_vgpu_err("fail: shadow page %p guest entry 0x%llx type %d.\n",
			spt, we->val64, we->type);
	return ret;
}