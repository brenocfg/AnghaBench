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
struct nvkm_pci {int dummy; } ;
typedef  enum nvkm_pcie_speed { ____Placeholder_nvkm_pcie_speed } nvkm_pcie_speed ;

/* Variables and functions */
 int NVKM_PCIE_SPEED_5_0 ; 
 int /*<<< orphan*/  nvkm_pci_mask (struct nvkm_pci*,int,int,int) ; 

void
g84_pcie_set_link_speed(struct nvkm_pci *pci, enum nvkm_pcie_speed speed)
{
	u32 mask_value;

	if (speed == NVKM_PCIE_SPEED_5_0)
		mask_value = 0x20;
	else
		mask_value = 0x10;

	nvkm_pci_mask(pci, 0x460, 0x30, mask_value);
	nvkm_pci_mask(pci, 0x460, 0x1, 0x1);
}