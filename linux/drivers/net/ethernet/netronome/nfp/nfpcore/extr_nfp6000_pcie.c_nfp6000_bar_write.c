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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_bar {int index; int /*<<< orphan*/  barcfg; } ;
struct TYPE_2__ {scalar_t__ csr; } ;
struct nfp6000_pcie {int /*<<< orphan*/  pdev; TYPE_1__ iomem; } ;

/* Variables and functions */
 int NFP_PCIE_CFG_BAR_PCIETOCPPEXPANSIONBAR (int,int) ; 
 int NFP_PCIE_CPP_BAR_PCIETOCPPEXPANSIONBAR (int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nfp6000_bar_write(struct nfp6000_pcie *nfp, struct nfp_bar *bar, u32 newcfg)
{
	int base, slot;
	int xbar;

	base = bar->index >> 3;
	slot = bar->index & 7;

	if (nfp->iomem.csr) {
		xbar = NFP_PCIE_CPP_BAR_PCIETOCPPEXPANSIONBAR(base, slot);
		writel(newcfg, nfp->iomem.csr + xbar);
		/* Readback to ensure BAR is flushed */
		readl(nfp->iomem.csr + xbar);
	} else {
		xbar = NFP_PCIE_CFG_BAR_PCIETOCPPEXPANSIONBAR(base, slot);
		pci_write_config_dword(nfp->pdev, xbar, newcfg);
	}

	bar->barcfg = newcfg;

	return 0;
}