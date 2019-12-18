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
typedef  int u32 ;
struct intel_vgpu {int dummy; } ;
struct TYPE_4__ {int hypervisor_type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * gfn; int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INTEL_GVT_HYPERVISOR_KVM 129 
#define  INTEL_GVT_HYPERVISOR_XEN 128 
 int INTEL_GVT_OPREGION_PAGES ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  gvt_dbg_core (char*) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 TYPE_2__ intel_gvt_host ; 
 int map_vgpu_opregion (struct intel_vgpu*,int) ; 
 TYPE_1__* vgpu_opregion (struct intel_vgpu*) ; 

int intel_vgpu_opregion_base_write_handler(struct intel_vgpu *vgpu, u32 gpa)
{

	int i, ret = 0;

	gvt_dbg_core("emulate opregion from kernel\n");

	switch (intel_gvt_host.hypervisor_type) {
	case INTEL_GVT_HYPERVISOR_KVM:
		for (i = 0; i < INTEL_GVT_OPREGION_PAGES; i++)
			vgpu_opregion(vgpu)->gfn[i] = (gpa >> PAGE_SHIFT) + i;
		break;
	case INTEL_GVT_HYPERVISOR_XEN:
		/**
		 * Wins guest on Xengt will write this register twice: xen
		 * hvmloader and windows graphic driver.
		 */
		if (vgpu_opregion(vgpu)->mapped)
			map_vgpu_opregion(vgpu, false);

		for (i = 0; i < INTEL_GVT_OPREGION_PAGES; i++)
			vgpu_opregion(vgpu)->gfn[i] = (gpa >> PAGE_SHIFT) + i;

		ret = map_vgpu_opregion(vgpu, true);
		break;
	default:
		ret = -EINVAL;
		gvt_vgpu_err("not supported hypervisor\n");
	}

	return ret;
}