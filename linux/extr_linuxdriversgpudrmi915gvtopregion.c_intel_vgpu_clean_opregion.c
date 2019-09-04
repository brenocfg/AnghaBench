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
struct intel_vgpu {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ hypervisor_type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * va; scalar_t__ mapped; } ;

/* Variables and functions */
 scalar_t__ INTEL_GVT_HYPERVISOR_KVM ; 
 scalar_t__ INTEL_GVT_HYPERVISOR_XEN ; 
 int /*<<< orphan*/  INTEL_GVT_OPREGION_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ intel_gvt_host ; 
 int /*<<< orphan*/  map_vgpu_opregion (struct intel_vgpu*,int) ; 
 TYPE_1__* vgpu_opregion (struct intel_vgpu*) ; 

void intel_vgpu_clean_opregion(struct intel_vgpu *vgpu)
{
	gvt_dbg_core("vgpu%d: clean vgpu opregion\n", vgpu->id);

	if (!vgpu_opregion(vgpu)->va)
		return;

	if (intel_gvt_host.hypervisor_type == INTEL_GVT_HYPERVISOR_XEN) {
		if (vgpu_opregion(vgpu)->mapped)
			map_vgpu_opregion(vgpu, false);
	} else if (intel_gvt_host.hypervisor_type == INTEL_GVT_HYPERVISOR_KVM) {
		/* Guest opregion is released by VFIO */
	}
	free_pages((unsigned long)vgpu_opregion(vgpu)->va,
		   get_order(INTEL_GVT_OPREGION_SIZE));

	vgpu_opregion(vgpu)->va = NULL;

}