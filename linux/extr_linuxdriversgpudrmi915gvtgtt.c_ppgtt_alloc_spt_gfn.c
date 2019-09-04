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
struct TYPE_3__ {int /*<<< orphan*/  mfn; } ;
struct TYPE_4__ {unsigned long gfn; int pde_ips; int /*<<< orphan*/  type; } ;
struct intel_vgpu_ppgtt_spt {TYPE_1__ shadow_page; TYPE_2__ guest_page; } ;
struct intel_vgpu {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  intel_gvt_gtt_type_t ;

/* Variables and functions */
 struct intel_vgpu_ppgtt_spt* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct intel_vgpu_ppgtt_spt*) ; 
 int intel_vgpu_register_page_track (struct intel_vgpu*,unsigned long,int /*<<< orphan*/ ,struct intel_vgpu_ppgtt_spt*) ; 
 struct intel_vgpu_ppgtt_spt* ppgtt_alloc_spt (struct intel_vgpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppgtt_free_spt (struct intel_vgpu_ppgtt_spt*) ; 
 int /*<<< orphan*/  ppgtt_write_protection_handler ; 
 int /*<<< orphan*/  trace_spt_alloc (int /*<<< orphan*/ ,struct intel_vgpu_ppgtt_spt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct intel_vgpu_ppgtt_spt *ppgtt_alloc_spt_gfn(
		struct intel_vgpu *vgpu, intel_gvt_gtt_type_t type,
		unsigned long gfn, bool guest_pde_ips)
{
	struct intel_vgpu_ppgtt_spt *spt;
	int ret;

	spt = ppgtt_alloc_spt(vgpu, type);
	if (IS_ERR(spt))
		return spt;

	/*
	 * Init guest_page.
	 */
	ret = intel_vgpu_register_page_track(vgpu, gfn,
			ppgtt_write_protection_handler, spt);
	if (ret) {
		ppgtt_free_spt(spt);
		return ERR_PTR(ret);
	}

	spt->guest_page.type = type;
	spt->guest_page.gfn = gfn;
	spt->guest_page.pde_ips = guest_pde_ips;

	trace_spt_alloc(vgpu->id, spt, type, spt->shadow_page.mfn, gfn);

	return spt;
}