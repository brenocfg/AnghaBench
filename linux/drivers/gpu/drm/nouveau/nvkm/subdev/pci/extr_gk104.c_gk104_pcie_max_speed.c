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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_pci {TYPE_1__ subdev; } ;
typedef  enum nvkm_pcie_speed { ____Placeholder_nvkm_pcie_speed } nvkm_pcie_speed ;

/* Variables and functions */
 int NVKM_PCIE_SPEED_2_5 ; 
 int NVKM_PCIE_SPEED_5_0 ; 
 int NVKM_PCIE_SPEED_8_0 ; 
 int nvkm_rd32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum nvkm_pcie_speed
gk104_pcie_max_speed(struct nvkm_pci *pci)
{
	u32 max_speed = nvkm_rd32(pci->subdev.device, 0x8c1c0) & 0x300000;
	switch (max_speed) {
	case 0x000000:
		return NVKM_PCIE_SPEED_8_0;
	case 0x100000:
		return NVKM_PCIE_SPEED_5_0;
	case 0x200000:
		return NVKM_PCIE_SPEED_2_5;
	}
	return NVKM_PCIE_SPEED_2_5;
}