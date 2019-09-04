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
typedef  int u64 ;
typedef  int u32 ;
struct intel_vgpu {int dummy; } ;
typedef  int /*<<< orphan*/  scic ;
typedef  int /*<<< orphan*/  parm ;
struct TYPE_4__ {int hypervisor_type; } ;
struct TYPE_3__ {int* gfn; scalar_t__ va; } ;

/* Variables and functions */
 int EINVAL ; 
 int GVT_OPREGION_FUNC (int) ; 
 int GVT_OPREGION_SUBFUNC (int) ; 
#define  INTEL_GVT_HYPERVISOR_KVM 129 
#define  INTEL_GVT_HYPERVISOR_XEN 128 
 int INTEL_GVT_OPREGION_PARM ; 
 int INTEL_GVT_OPREGION_SCIC ; 
 size_t INTEL_GVT_PCI_SWSCI ; 
 int OPREGION_SCIC_EXIT_MASK ; 
 int PAGE_SHIFT ; 
 int SWSCI_SCI_SELECT ; 
 int SWSCI_SCI_TRIGGER ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,...) ; 
 TYPE_2__ intel_gvt_host ; 
 int intel_gvt_hypervisor_read_gpa (struct intel_vgpu*,int,int*,int) ; 
 int intel_gvt_hypervisor_write_gpa (struct intel_vgpu*,int,int*,int) ; 
 int /*<<< orphan*/  opregion_func_name (int) ; 
 int /*<<< orphan*/  opregion_subfunc_name (int) ; 
 int /*<<< orphan*/  querying_capabilities (int) ; 
 int* vgpu_cfg_space (struct intel_vgpu*) ; 
 TYPE_1__* vgpu_opregion (struct intel_vgpu*) ; 

int intel_vgpu_emulate_opregion_request(struct intel_vgpu *vgpu, u32 swsci)
{
	u32 scic, parm;
	u32 func, subfunc;
	u64 scic_pa = 0, parm_pa = 0;
	int ret;

	switch (intel_gvt_host.hypervisor_type) {
	case INTEL_GVT_HYPERVISOR_XEN:
		scic = *((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_SCIC);
		parm = *((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_PARM);
		break;
	case INTEL_GVT_HYPERVISOR_KVM:
		scic_pa = (vgpu_opregion(vgpu)->gfn[0] << PAGE_SHIFT) +
					INTEL_GVT_OPREGION_SCIC;
		parm_pa = (vgpu_opregion(vgpu)->gfn[0] << PAGE_SHIFT) +
					INTEL_GVT_OPREGION_PARM;

		ret = intel_gvt_hypervisor_read_gpa(vgpu, scic_pa,
						    &scic, sizeof(scic));
		if (ret) {
			gvt_vgpu_err("guest opregion read error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, sizeof(scic));
			return ret;
		}

		ret = intel_gvt_hypervisor_read_gpa(vgpu, parm_pa,
						    &parm, sizeof(parm));
		if (ret) {
			gvt_vgpu_err("guest opregion read error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, sizeof(scic));
			return ret;
		}

		break;
	default:
		gvt_vgpu_err("not supported hypervisor\n");
		return -EINVAL;
	}

	if (!(swsci & SWSCI_SCI_SELECT)) {
		gvt_vgpu_err("requesting SMI service\n");
		return 0;
	}
	/* ignore non 0->1 trasitions */
	if ((vgpu_cfg_space(vgpu)[INTEL_GVT_PCI_SWSCI]
				& SWSCI_SCI_TRIGGER) ||
			!(swsci & SWSCI_SCI_TRIGGER)) {
		return 0;
	}

	func = GVT_OPREGION_FUNC(scic);
	subfunc = GVT_OPREGION_SUBFUNC(scic);
	if (!querying_capabilities(scic)) {
		gvt_vgpu_err("requesting runtime service: func \"%s\","
				" subfunc \"%s\"\n",
				opregion_func_name(func),
				opregion_subfunc_name(subfunc));
		/*
		 * emulate exit status of function call, '0' means
		 * "failure, generic, unsupported or unknown cause"
		 */
		scic &= ~OPREGION_SCIC_EXIT_MASK;
		goto out;
	}

	scic = 0;
	parm = 0;

out:
	switch (intel_gvt_host.hypervisor_type) {
	case INTEL_GVT_HYPERVISOR_XEN:
		*((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_SCIC) = scic;
		*((u32 *)vgpu_opregion(vgpu)->va +
					INTEL_GVT_OPREGION_PARM) = parm;
		break;
	case INTEL_GVT_HYPERVISOR_KVM:
		ret = intel_gvt_hypervisor_write_gpa(vgpu, scic_pa,
						    &scic, sizeof(scic));
		if (ret) {
			gvt_vgpu_err("guest opregion write error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, sizeof(scic));
			return ret;
		}

		ret = intel_gvt_hypervisor_write_gpa(vgpu, parm_pa,
						    &parm, sizeof(parm));
		if (ret) {
			gvt_vgpu_err("guest opregion write error %d, gpa 0x%llx, len %lu\n",
				ret, scic_pa, sizeof(scic));
			return ret;
		}

		break;
	default:
		gvt_vgpu_err("not supported hypervisor\n");
		return -EINVAL;
	}

	return 0;
}