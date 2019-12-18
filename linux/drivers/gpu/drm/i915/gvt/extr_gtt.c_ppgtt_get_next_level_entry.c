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
struct intel_vgpu_ppgtt_spt {int dummy; } ;
struct intel_vgpu_mm {struct intel_vgpu* vgpu; } ;
struct intel_vgpu {TYPE_2__* gvt; } ;
struct intel_gvt_gtt_pte_ops {int /*<<< orphan*/  (* get_pfn ) (struct intel_gvt_gtt_entry*) ;} ;
struct intel_gvt_gtt_entry {int dummy; } ;
struct TYPE_3__ {struct intel_gvt_gtt_pte_ops* pte_ops; } ;
struct TYPE_4__ {TYPE_1__ gtt; } ;

/* Variables and functions */
 int ENXIO ; 
 struct intel_vgpu_ppgtt_spt* intel_vgpu_find_spt_by_mfn (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppgtt_get_guest_entry (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  ppgtt_get_shadow_entry (struct intel_vgpu_ppgtt_spt*,struct intel_gvt_gtt_entry*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct intel_gvt_gtt_entry*) ; 

__attribute__((used)) static inline int ppgtt_get_next_level_entry(struct intel_vgpu_mm *mm,
		struct intel_gvt_gtt_entry *e, unsigned long index, bool guest)
{
	struct intel_vgpu *vgpu = mm->vgpu;
	struct intel_gvt_gtt_pte_ops *ops = vgpu->gvt->gtt.pte_ops;
	struct intel_vgpu_ppgtt_spt *s;

	s = intel_vgpu_find_spt_by_mfn(vgpu, ops->get_pfn(e));
	if (!s)
		return -ENXIO;

	if (!guest)
		ppgtt_get_shadow_entry(s, e, index);
	else
		ppgtt_get_guest_entry(s, e, index);
	return 0;
}