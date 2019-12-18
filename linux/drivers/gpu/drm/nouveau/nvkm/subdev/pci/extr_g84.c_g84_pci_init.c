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
struct nvkm_pci {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_pci_mask (struct nvkm_pci*,int,int,int) ; 
 int nvkm_pci_rd32 (struct nvkm_pci*,int) ; 
 int /*<<< orphan*/  pci_is_pcie (int /*<<< orphan*/ ) ; 

void
g84_pci_init(struct nvkm_pci *pci)
{
	/* The following only concerns PCIe cards. */
	if (!pci_is_pcie(pci->pdev))
		return;

	/* Tag field is 8-bit long, regardless of EXT_TAG.
	 * However, if EXT_TAG is disabled, only the lower 5 bits of the tag
	 * field should be used, limiting the number of request to 32.
	 *
	 * Apparently, 0x041c stores some limit on the number of requests
	 * possible, so if EXT_TAG is disabled, limit that requests number to
	 * 32
	 *
	 * Fixes fdo#86537
	 */
	if (nvkm_pci_rd32(pci, 0x007c) & 0x00000020)
		nvkm_pci_mask(pci, 0x0080, 0x00000100, 0x00000100);
	else
		nvkm_pci_mask(pci, 0x041c, 0x00000060, 0x00000000);
}