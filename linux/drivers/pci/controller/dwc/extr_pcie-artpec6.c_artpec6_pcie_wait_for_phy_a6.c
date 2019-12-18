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
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;
struct artpec6_pcie {scalar_t__ phy_base; struct dw_pcie* pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOCCFG ; 
 int NOCCFG_POWER_PCIE_IDLE ; 
 int NOCCFG_POWER_PCIE_IDLEACK ; 
 int PHY_COSPLLLOCK ; 
 scalar_t__ PHY_STATUS ; 
 int artpec6_pcie_readl (struct artpec6_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void artpec6_pcie_wait_for_phy_a6(struct artpec6_pcie *artpec6_pcie)
{
	struct dw_pcie *pci = artpec6_pcie->pci;
	struct device *dev = pci->dev;
	u32 val;
	unsigned int retries;

	retries = 50;
	do {
		usleep_range(1000, 2000);
		val = artpec6_pcie_readl(artpec6_pcie, NOCCFG);
		retries--;
	} while (retries &&
		(val & (NOCCFG_POWER_PCIE_IDLEACK | NOCCFG_POWER_PCIE_IDLE)));
	if (!retries)
		dev_err(dev, "PCIe clock manager did not leave idle state\n");

	retries = 50;
	do {
		usleep_range(1000, 2000);
		val = readl(artpec6_pcie->phy_base + PHY_STATUS);
		retries--;
	} while (retries && !(val & PHY_COSPLLLOCK));
	if (!retries)
		dev_err(dev, "PHY PLL did not lock\n");
}