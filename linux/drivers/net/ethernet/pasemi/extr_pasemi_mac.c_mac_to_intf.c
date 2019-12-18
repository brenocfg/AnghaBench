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
struct pci_dev {int devfn; } ;
struct pasemi_mac {struct pci_dev* pdev; } ;

/* Variables and functions */
 int PAS_DMA_CAP_IFI ; 
 int PAS_DMA_CAP_IFI_IOFF_M ; 
 int PAS_DMA_CAP_IFI_IOFF_S ; 
 int PAS_DMA_CAP_IFI_NIN_M ; 
 int PAS_DMA_CAP_IFI_NIN_S ; 
 int read_dma_reg (int) ; 

__attribute__((used)) static int mac_to_intf(struct pasemi_mac *mac)
{
	struct pci_dev *pdev = mac->pdev;
	u32 tmp;
	int nintf, off, i, j;
	int devfn = pdev->devfn;

	tmp = read_dma_reg(PAS_DMA_CAP_IFI);
	nintf = (tmp & PAS_DMA_CAP_IFI_NIN_M) >> PAS_DMA_CAP_IFI_NIN_S;
	off = (tmp & PAS_DMA_CAP_IFI_IOFF_M) >> PAS_DMA_CAP_IFI_IOFF_S;

	/* IOFF contains the offset to the registers containing the
	 * DMA interface-to-MAC-pci-id mappings, and NIN contains number
	 * of total interfaces. Each register contains 4 devfns.
	 * Just do a linear search until we find the devfn of the MAC
	 * we're trying to look up.
	 */

	for (i = 0; i < (nintf+3)/4; i++) {
		tmp = read_dma_reg(off+4*i);
		for (j = 0; j < 4; j++) {
			if (((tmp >> (8*j)) & 0xff) == devfn)
				return i*4 + j;
		}
	}
	return -1;
}