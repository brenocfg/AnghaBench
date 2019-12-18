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
typedef  int u32 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int PCI_ROM_ADDRESS_MASK ; 
 scalar_t__ vgpu_cfg_space (struct intel_vgpu*) ; 
 int /*<<< orphan*/  vgpu_pci_cfg_mem_write (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int emulate_pci_rom_bar_write(struct intel_vgpu *vgpu,
	unsigned int offset, void *p_data, unsigned int bytes)
{
	u32 *pval = (u32 *)(vgpu_cfg_space(vgpu) + offset);
	u32 new = *(u32 *)(p_data);

	if ((new & PCI_ROM_ADDRESS_MASK) == PCI_ROM_ADDRESS_MASK)
		/* We don't have rom, return size of 0. */
		*pval = 0;
	else
		vgpu_pci_cfg_mem_write(vgpu, offset, p_data, bytes);
	return 0;
}