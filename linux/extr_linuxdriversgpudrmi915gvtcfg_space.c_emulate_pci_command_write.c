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
 int PCI_COMMAND_MEMORY ; 
 int map_aperture (struct intel_vgpu*,int) ; 
 int trap_gttmmio (struct intel_vgpu*,int) ; 
 int* vgpu_cfg_space (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_pci_cfg_mem_write (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int emulate_pci_command_write(struct intel_vgpu *vgpu,
	unsigned int offset, void *p_data, unsigned int bytes)
{
	u8 old = vgpu_cfg_space(vgpu)[offset];
	u8 new = *(u8 *)p_data;
	u8 changed = old ^ new;
	int ret;

	vgpu_pci_cfg_mem_write(vgpu, offset, p_data, bytes);
	if (!(changed & PCI_COMMAND_MEMORY))
		return 0;

	if (old & PCI_COMMAND_MEMORY) {
		ret = trap_gttmmio(vgpu, false);
		if (ret)
			return ret;
		ret = map_aperture(vgpu, false);
		if (ret)
			return ret;
	} else {
		ret = trap_gttmmio(vgpu, true);
		if (ret)
			return ret;
		ret = map_aperture(vgpu, true);
		if (ret)
			return ret;
	}

	return 0;
}