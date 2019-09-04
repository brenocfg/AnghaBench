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
struct nvkm_pci {int dummy; } ;
typedef  enum nvkm_pcie_speed { ____Placeholder_nvkm_pcie_speed } nvkm_pcie_speed ;

/* Variables and functions */
#define  NVKM_PCIE_SPEED_2_5 130 
#define  NVKM_PCIE_SPEED_5_0 129 
#define  NVKM_PCIE_SPEED_8_0 128 
 int /*<<< orphan*/  nvkm_pci_mask (struct nvkm_pci*,int,int,int) ; 

__attribute__((used)) static void
gk104_pcie_set_lnkctl_speed(struct nvkm_pci *pci, enum nvkm_pcie_speed speed)
{
	u8 reg_v = 0;
	switch (speed) {
	case NVKM_PCIE_SPEED_2_5:
		reg_v = 1;
		break;
	case NVKM_PCIE_SPEED_5_0:
		reg_v = 2;
		break;
	case NVKM_PCIE_SPEED_8_0:
		reg_v = 3;
		break;
	}
	nvkm_pci_mask(pci, 0xa8, 0x3, reg_v);
}