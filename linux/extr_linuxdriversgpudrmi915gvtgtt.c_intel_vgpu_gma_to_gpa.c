#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ root_entry_type; } ;
struct intel_vgpu_mm {scalar_t__ type; TYPE_2__ ppgtt_mm; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  id; struct intel_gvt* gvt; } ;
struct intel_gvt_gtt_pte_ops {unsigned long (* get_pfn ) (struct intel_gvt_gtt_entry*) ;int /*<<< orphan*/  (* test_present ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_gma_ops {unsigned long (* gma_to_pml4_index ) (unsigned long) ;unsigned long (* gma_to_l4_pdp_index ) (unsigned long) ;unsigned long (* gma_to_pde_index ) (unsigned long) ;unsigned long (* gma_to_pte_index ) (unsigned long) ;int /*<<< orphan*/  (* gma_to_l3_pdp_index ) (unsigned long) ;int /*<<< orphan*/  (* gma_to_ggtt_pte_index ) (unsigned long) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_3__ {struct intel_gvt_gtt_gma_ops* gma_ops; struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct intel_gvt {TYPE_1__ gtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
#define  GTT_TYPE_PPGTT_ROOT_L3_ENTRY 129 
#define  GTT_TYPE_PPGTT_ROOT_L4_ENTRY 128 
 unsigned long I915_GTT_PAGE_MASK ; 
 unsigned long I915_GTT_PAGE_SHIFT ; 
 unsigned long INTEL_GVT_INVALID_ADDR ; 
 scalar_t__ INTEL_GVT_MM_GGTT ; 
 scalar_t__ INTEL_GVT_MM_PPGTT ; 
 int /*<<< orphan*/  ggtt_get_guest_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,unsigned long) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,scalar_t__,unsigned long) ; 
 int ppgtt_get_next_level_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,unsigned long,int) ; 
 int /*<<< orphan*/  ppgtt_get_shadow_root_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 
 int /*<<< orphan*/  stub10 (struct intel_gvt_gtt_entry*) ; 
 unsigned long stub11 (struct intel_gvt_gtt_entry*) ; 
 unsigned long stub2 (struct intel_gvt_gtt_entry*) ; 
 unsigned long stub3 (unsigned long) ; 
 unsigned long stub4 (unsigned long) ; 
 unsigned long stub5 (unsigned long) ; 
 unsigned long stub6 (unsigned long) ; 
 int /*<<< orphan*/  stub7 (unsigned long) ; 
 unsigned long stub8 (unsigned long) ; 
 unsigned long stub9 (unsigned long) ; 
 int /*<<< orphan*/  trace_gma_translate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vgpu_gmadr_is_valid (struct intel_vgpu*,unsigned long) ; 

unsigned long intel_vgpu_gma_to_gpa(struct intel_vgpu_mm *mm, unsigned long gma)
{
	struct intel_vgpu *vgpu = mm->vgpu;
	struct intel_gvt *gvt = vgpu->gvt;
	struct intel_gvt_gtt_pte_ops *pte_ops = gvt->gtt.pte_ops;
	struct intel_gvt_gtt_gma_ops *gma_ops = gvt->gtt.gma_ops;
	unsigned long gpa = INTEL_GVT_INVALID_ADDR;
	unsigned long gma_index[4];
	struct intel_gvt_gtt_entry e;
	int i, levels = 0;
	int ret;

	GEM_BUG_ON(mm->type != INTEL_GVT_MM_GGTT &&
		   mm->type != INTEL_GVT_MM_PPGTT);

	if (mm->type == INTEL_GVT_MM_GGTT) {
		if (!vgpu_gmadr_is_valid(vgpu, gma))
			goto err;

		ggtt_get_guest_entry(mm, &e,
			gma_ops->gma_to_ggtt_pte_index(gma));

		gpa = (pte_ops->get_pfn(&e) << I915_GTT_PAGE_SHIFT)
			+ (gma & ~I915_GTT_PAGE_MASK);

		trace_gma_translate(vgpu->id, "ggtt", 0, 0, gma, gpa);
	} else {
		switch (mm->ppgtt_mm.root_entry_type) {
		case GTT_TYPE_PPGTT_ROOT_L4_ENTRY:
			ppgtt_get_shadow_root_entry(mm, &e, 0);

			gma_index[0] = gma_ops->gma_to_pml4_index(gma);
			gma_index[1] = gma_ops->gma_to_l4_pdp_index(gma);
			gma_index[2] = gma_ops->gma_to_pde_index(gma);
			gma_index[3] = gma_ops->gma_to_pte_index(gma);
			levels = 4;
			break;
		case GTT_TYPE_PPGTT_ROOT_L3_ENTRY:
			ppgtt_get_shadow_root_entry(mm, &e,
					gma_ops->gma_to_l3_pdp_index(gma));

			gma_index[0] = gma_ops->gma_to_pde_index(gma);
			gma_index[1] = gma_ops->gma_to_pte_index(gma);
			levels = 2;
			break;
		default:
			GEM_BUG_ON(1);
		}

		/* walk the shadow page table and get gpa from guest entry */
		for (i = 0; i < levels; i++) {
			ret = ppgtt_get_next_level_entry(mm, &e, gma_index[i],
				(i == levels - 1));
			if (ret)
				goto err;

			if (!pte_ops->test_present(&e)) {
				gvt_dbg_core("GMA 0x%lx is not present\n", gma);
				goto err;
			}
		}

		gpa = (pte_ops->get_pfn(&e) << I915_GTT_PAGE_SHIFT) +
					(gma & ~I915_GTT_PAGE_MASK);
		trace_gma_translate(vgpu->id, "ppgtt", 0,
				    mm->ppgtt_mm.root_entry_type, gma, gpa);
	}

	return gpa;
err:
	gvt_vgpu_err("invalid mm type: %d gma %lx\n", mm->type, gma);
	return INTEL_GVT_INVALID_ADDR;
}