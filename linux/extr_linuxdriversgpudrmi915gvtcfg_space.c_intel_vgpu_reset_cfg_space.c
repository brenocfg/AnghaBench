#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTEL_GVT_PCI_CLASS_VGA_OTHER ; 
 size_t PCI_CLASS_DEVICE ; 
 size_t PCI_COMMAND ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  intel_vgpu_init_cfg_space (struct intel_vgpu*,int) ; 
 int /*<<< orphan*/  map_aperture (struct intel_vgpu*,int) ; 
 int /*<<< orphan*/  trap_gttmmio (struct intel_vgpu*,int) ; 
 scalar_t__* vgpu_cfg_space (struct intel_vgpu*) ; 

void intel_vgpu_reset_cfg_space(struct intel_vgpu *vgpu)
{
	u8 cmd = vgpu_cfg_space(vgpu)[PCI_COMMAND];
	bool primary = vgpu_cfg_space(vgpu)[PCI_CLASS_DEVICE] !=
				INTEL_GVT_PCI_CLASS_VGA_OTHER;

	if (cmd & PCI_COMMAND_MEMORY) {
		trap_gttmmio(vgpu, false);
		map_aperture(vgpu, false);
	}

	/**
	 * Currently we only do such reset when vGPU is not
	 * owned by any VM, so we simply restore entire cfg
	 * space to default value.
	 */
	intel_vgpu_init_cfg_space(vgpu, primary);
}