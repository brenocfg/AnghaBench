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
struct pcidev_info {int dummy; } ;
struct pci_dev {int dma_mask; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI32_ATE_PREF ; 
 int /*<<< orphan*/  PCI64_ATTR_PREF ; 
 struct pcidev_info* SN_PCIDEV_INFO (struct pci_dev*) ; 
 scalar_t__ pcibr_dmamap_ate32 (struct pcidev_info*,unsigned long,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcibr_dmatrans_direct32 (struct pcidev_info*,unsigned long,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pcibr_dmatrans_direct64 (struct pcidev_info*,unsigned long,int /*<<< orphan*/ ,int) ; 

dma_addr_t
pcibr_dma_map(struct pci_dev * hwdev, unsigned long phys_addr, size_t size, int dma_flags)
{
	dma_addr_t dma_handle;
	struct pcidev_info *pcidev_info = SN_PCIDEV_INFO(hwdev);

	/* SN cannot support DMA addresses smaller than 32 bits. */
	if (hwdev->dma_mask < 0x7fffffff) {
		return 0;
	}

	if (hwdev->dma_mask == ~0UL) {
		/*
		 * Handle the most common case: 64 bit cards.  This
		 * call should always succeed.
		 */

		dma_handle = pcibr_dmatrans_direct64(pcidev_info, phys_addr,
						     PCI64_ATTR_PREF, dma_flags);
	} else {
		/* Handle 32-63 bit cards via direct mapping */
		dma_handle = pcibr_dmatrans_direct32(pcidev_info, phys_addr,
						     size, 0, dma_flags);
		if (!dma_handle) {
			/*
			 * It is a 32 bit card and we cannot do direct mapping,
			 * so we use an ATE.
			 */

			dma_handle = pcibr_dmamap_ate32(pcidev_info, phys_addr,
							size, PCI32_ATE_PREF,
							dma_flags);
		}
	}

	return dma_handle;
}