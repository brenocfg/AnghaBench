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
struct nvkm_pci {int dummy; } ;

/* Variables and functions */
 int nvkm_pci_rd32 (struct nvkm_pci*,int) ; 

int
g92_pcie_version_supported(struct nvkm_pci *pci)
{
	if ((nvkm_pci_rd32(pci, 0x460) & 0x200) == 0x200)
		return 2;
	return 1;
}