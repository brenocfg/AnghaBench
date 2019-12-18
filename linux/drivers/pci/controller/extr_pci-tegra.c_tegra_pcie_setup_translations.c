#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int start; } ;
struct tegra_pcie {TYPE_1__* soc; TYPE_2__ mem; TYPE_2__ prefetch; TYPE_2__ io; TYPE_2__ cs; } ;
struct TYPE_3__ {scalar_t__ has_cache_bars; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_AXI_BAR0_START ; 
 int /*<<< orphan*/  AFI_AXI_BAR0_SZ ; 
 int /*<<< orphan*/  AFI_AXI_BAR1_START ; 
 int /*<<< orphan*/  AFI_AXI_BAR1_SZ ; 
 int /*<<< orphan*/  AFI_AXI_BAR2_START ; 
 int /*<<< orphan*/  AFI_AXI_BAR2_SZ ; 
 int /*<<< orphan*/  AFI_AXI_BAR3_START ; 
 int /*<<< orphan*/  AFI_AXI_BAR3_SZ ; 
 int /*<<< orphan*/  AFI_AXI_BAR4_START ; 
 int /*<<< orphan*/  AFI_AXI_BAR4_SZ ; 
 int /*<<< orphan*/  AFI_AXI_BAR5_START ; 
 int /*<<< orphan*/  AFI_AXI_BAR5_SZ ; 
 int /*<<< orphan*/  AFI_CACHE_BAR0_ST ; 
 int /*<<< orphan*/  AFI_CACHE_BAR0_SZ ; 
 int /*<<< orphan*/  AFI_CACHE_BAR1_ST ; 
 int /*<<< orphan*/  AFI_CACHE_BAR1_SZ ; 
 int /*<<< orphan*/  AFI_FPCI_BAR1 ; 
 int /*<<< orphan*/  AFI_FPCI_BAR2 ; 
 int /*<<< orphan*/  AFI_FPCI_BAR3 ; 
 int /*<<< orphan*/  AFI_FPCI_BAR4 ; 
 int /*<<< orphan*/  AFI_FPCI_BAR5 ; 
 int /*<<< orphan*/  AFI_MSI_AXI_BAR_ST ; 
 int /*<<< orphan*/  AFI_MSI_BAR_SZ ; 
 int /*<<< orphan*/  AFI_MSI_FPCI_BAR_ST ; 
 int /*<<< orphan*/  afi_writel (struct tegra_pcie*,int,int /*<<< orphan*/ ) ; 
 int resource_size (TYPE_2__*) ; 

__attribute__((used)) static void tegra_pcie_setup_translations(struct tegra_pcie *pcie)
{
	u32 fpci_bar, size, axi_address;

	/* Bar 0: type 1 extended configuration space */
	size = resource_size(&pcie->cs);
	afi_writel(pcie, pcie->cs.start, AFI_AXI_BAR0_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR0_SZ);

	/* Bar 1: downstream IO bar */
	fpci_bar = 0xfdfc0000;
	size = resource_size(&pcie->io);
	axi_address = pcie->io.start;
	afi_writel(pcie, axi_address, AFI_AXI_BAR1_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR1_SZ);
	afi_writel(pcie, fpci_bar, AFI_FPCI_BAR1);

	/* Bar 2: prefetchable memory BAR */
	fpci_bar = (((pcie->prefetch.start >> 12) & 0x0fffffff) << 4) | 0x1;
	size = resource_size(&pcie->prefetch);
	axi_address = pcie->prefetch.start;
	afi_writel(pcie, axi_address, AFI_AXI_BAR2_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR2_SZ);
	afi_writel(pcie, fpci_bar, AFI_FPCI_BAR2);

	/* Bar 3: non prefetchable memory BAR */
	fpci_bar = (((pcie->mem.start >> 12) & 0x0fffffff) << 4) | 0x1;
	size = resource_size(&pcie->mem);
	axi_address = pcie->mem.start;
	afi_writel(pcie, axi_address, AFI_AXI_BAR3_START);
	afi_writel(pcie, size >> 12, AFI_AXI_BAR3_SZ);
	afi_writel(pcie, fpci_bar, AFI_FPCI_BAR3);

	/* NULL out the remaining BARs as they are not used */
	afi_writel(pcie, 0, AFI_AXI_BAR4_START);
	afi_writel(pcie, 0, AFI_AXI_BAR4_SZ);
	afi_writel(pcie, 0, AFI_FPCI_BAR4);

	afi_writel(pcie, 0, AFI_AXI_BAR5_START);
	afi_writel(pcie, 0, AFI_AXI_BAR5_SZ);
	afi_writel(pcie, 0, AFI_FPCI_BAR5);

	if (pcie->soc->has_cache_bars) {
		/* map all upstream transactions as uncached */
		afi_writel(pcie, 0, AFI_CACHE_BAR0_ST);
		afi_writel(pcie, 0, AFI_CACHE_BAR0_SZ);
		afi_writel(pcie, 0, AFI_CACHE_BAR1_ST);
		afi_writel(pcie, 0, AFI_CACHE_BAR1_SZ);
	}

	/* MSI translations are setup only when needed */
	afi_writel(pcie, 0, AFI_MSI_FPCI_BAR_ST);
	afi_writel(pcie, 0, AFI_MSI_BAR_SZ);
	afi_writel(pcie, 0, AFI_MSI_AXI_BAR_ST);
	afi_writel(pcie, 0, AFI_MSI_BAR_SZ);
}