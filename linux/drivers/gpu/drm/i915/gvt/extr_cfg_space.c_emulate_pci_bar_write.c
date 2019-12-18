#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct intel_vgpu_pci_bar {int /*<<< orphan*/  size; } ;
struct TYPE_2__ {struct intel_vgpu_pci_bar* bar; } ;
struct intel_vgpu {TYPE_1__ cfg_space; } ;

/* Variables and functions */
 size_t INTEL_GVT_PCI_BAR_APERTURE ; 
 size_t INTEL_GVT_PCI_BAR_GTTMMIO ; 
 int IS_ALIGNED (unsigned int,int) ; 
#define  PCI_BASE_ADDRESS_0 131 
#define  PCI_BASE_ADDRESS_1 130 
#define  PCI_BASE_ADDRESS_2 129 
#define  PCI_BASE_ADDRESS_3 128 
 size_t PCI_COMMAND ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  intel_vgpu_write_pci_bar (struct intel_vgpu*,unsigned int,int,int) ; 
 int map_aperture (struct intel_vgpu*,int) ; 
 int trap_gttmmio (struct intel_vgpu*,int) ; 
 int* vgpu_cfg_space (struct intel_vgpu*) ; 

__attribute__((used)) static int emulate_pci_bar_write(struct intel_vgpu *vgpu, unsigned int offset,
	void *p_data, unsigned int bytes)
{
	u32 new = *(u32 *)(p_data);
	bool lo = IS_ALIGNED(offset, 8);
	u64 size;
	int ret = 0;
	bool mmio_enabled =
		vgpu_cfg_space(vgpu)[PCI_COMMAND] & PCI_COMMAND_MEMORY;
	struct intel_vgpu_pci_bar *bars = vgpu->cfg_space.bar;

	/*
	 * Power-up software can determine how much address
	 * space the device requires by writing a value of
	 * all 1's to the register and then reading the value
	 * back. The device will return 0's in all don't-care
	 * address bits.
	 */
	if (new == 0xffffffff) {
		switch (offset) {
		case PCI_BASE_ADDRESS_0:
		case PCI_BASE_ADDRESS_1:
			size = ~(bars[INTEL_GVT_PCI_BAR_GTTMMIO].size -1);
			intel_vgpu_write_pci_bar(vgpu, offset,
						size >> (lo ? 0 : 32), lo);
			/*
			 * Untrap the BAR, since guest hasn't configured a
			 * valid GPA
			 */
			ret = trap_gttmmio(vgpu, false);
			break;
		case PCI_BASE_ADDRESS_2:
		case PCI_BASE_ADDRESS_3:
			size = ~(bars[INTEL_GVT_PCI_BAR_APERTURE].size -1);
			intel_vgpu_write_pci_bar(vgpu, offset,
						size >> (lo ? 0 : 32), lo);
			ret = map_aperture(vgpu, false);
			break;
		default:
			/* Unimplemented BARs */
			intel_vgpu_write_pci_bar(vgpu, offset, 0x0, false);
		}
	} else {
		switch (offset) {
		case PCI_BASE_ADDRESS_0:
		case PCI_BASE_ADDRESS_1:
			/*
			 * Untrap the old BAR first, since guest has
			 * re-configured the BAR
			 */
			trap_gttmmio(vgpu, false);
			intel_vgpu_write_pci_bar(vgpu, offset, new, lo);
			ret = trap_gttmmio(vgpu, mmio_enabled);
			break;
		case PCI_BASE_ADDRESS_2:
		case PCI_BASE_ADDRESS_3:
			map_aperture(vgpu, false);
			intel_vgpu_write_pci_bar(vgpu, offset, new, lo);
			ret = map_aperture(vgpu, mmio_enabled);
			break;
		default:
			intel_vgpu_write_pci_bar(vgpu, offset, new, lo);
		}
	}
	return ret;
}