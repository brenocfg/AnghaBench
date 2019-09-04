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
typedef  int u8 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_pci {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
gf100_pcie_cap_speed(struct nvkm_pci *pci)
{
	struct nvkm_device *device = pci->subdev.device;
	u8 punits_pci_cap_speed = nvkm_rd32(device, 0x02241c) & 0x80;
	if (punits_pci_cap_speed == 0x80)
		return 1;
	return 0;
}