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

/* Variables and functions */
 int nvkm_pci_rd32 (struct nvkm_pci*,int) ; 
 int /*<<< orphan*/  nvkm_pci_wr32 (struct nvkm_pci*,int,int) ; 

void
nvkm_pci_rom_shadow(struct nvkm_pci *pci, bool shadow)
{
	u32 data = nvkm_pci_rd32(pci, 0x0050);
	if (shadow)
		data |=  0x00000001;
	else
		data &= ~0x00000001;
	nvkm_pci_wr32(pci, 0x0050, data);
}