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
typedef  int /*<<< orphan*/  u32 ;
struct ar724x_pci_controller {scalar_t__ ctrl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR724X_PCI_APP_LTSSM_ENABLE ; 
 scalar_t__ AR724X_PCI_REG_APP ; 
 int /*<<< orphan*/  AR724X_PLL_REG_PCIE_CONFIG ; 
 int /*<<< orphan*/  AR724X_PLL_REG_PCIE_CONFIG_PPL_BYPASS ; 
 int /*<<< orphan*/  AR724X_PLL_REG_PCIE_CONFIG_PPL_RESET ; 
 int /*<<< orphan*/  AR724X_RESET_PCIE ; 
 int /*<<< orphan*/  AR724X_RESET_PCIE_PHY ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ar724x_pci_check_link (struct ar724x_pci_controller*) ; 
 int /*<<< orphan*/  ath79_device_reset_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_pll_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_pll_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void ar724x_pci_hw_init(struct ar724x_pci_controller *apc)
{
	u32 ppl, app;
	int wait = 0;

	/* deassert PCIe host controller and PCIe PHY reset */
	ath79_device_reset_clear(AR724X_RESET_PCIE);
	ath79_device_reset_clear(AR724X_RESET_PCIE_PHY);

	/* remove the reset of the PCIE PLL */
	ppl = ath79_pll_rr(AR724X_PLL_REG_PCIE_CONFIG);
	ppl &= ~AR724X_PLL_REG_PCIE_CONFIG_PPL_RESET;
	ath79_pll_wr(AR724X_PLL_REG_PCIE_CONFIG, ppl);

	/* deassert bypass for the PCIE PLL */
	ppl = ath79_pll_rr(AR724X_PLL_REG_PCIE_CONFIG);
	ppl &= ~AR724X_PLL_REG_PCIE_CONFIG_PPL_BYPASS;
	ath79_pll_wr(AR724X_PLL_REG_PCIE_CONFIG, ppl);

	/* set PCIE Application Control to ready */
	app = __raw_readl(apc->ctrl_base + AR724X_PCI_REG_APP);
	app |= AR724X_PCI_APP_LTSSM_ENABLE;
	__raw_writel(app, apc->ctrl_base + AR724X_PCI_REG_APP);

	/* wait up to 100ms for PHY link up */
	do {
		mdelay(10);
		wait++;
	} while (wait < 10 && !ar724x_pci_check_link(apc));
}