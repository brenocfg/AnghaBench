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
struct imx6_pcie {int gpio_active_high; scalar_t__ vpcie; int /*<<< orphan*/  pcie_phy; int /*<<< orphan*/  pcie_bus; int /*<<< orphan*/  pcie; int /*<<< orphan*/  iomuxc_gpr; scalar_t__ phy_base; int /*<<< orphan*/  pciephy_reset; TYPE_1__* drvdata; int /*<<< orphan*/  reset_gpio; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int variant; } ;

/* Variables and functions */
#define  IMX6Q 132 
#define  IMX6QP 131 
 int /*<<< orphan*/  IMX6Q_GPR1_PCIE_SW_RST ; 
#define  IMX6SX 130 
 int /*<<< orphan*/  IMX6SX_GPR5_PCIE_BTNRST_RESET ; 
#define  IMX7D 129 
#define  IMX8MQ 128 
 int /*<<< orphan*/  IOMUXC_GPR1 ; 
 int /*<<< orphan*/  IOMUXC_GPR5 ; 
 scalar_t__ PCIE_PHY_CMN_REG24 ; 
 int PCIE_PHY_CMN_REG24_RX_EQ ; 
 int PCIE_PHY_CMN_REG24_RX_EQ_SEL ; 
 scalar_t__ PCIE_PHY_CMN_REG26 ; 
 int PCIE_PHY_CMN_REG26_ATT_MODE ; 
 scalar_t__ PCIE_PHY_CMN_REG4 ; 
 int PCIE_PHY_CMN_REG4_DCC_FB_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int imx6_pcie_enable_ref_clk (struct imx6_pcie*) ; 
 int /*<<< orphan*/  imx7d_pcie_wait_for_phy_pll_lock (struct imx6_pcie*) ; 
 int /*<<< orphan*/  likely (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 scalar_t__ regulator_is_enabled (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imx6_pcie_deassert_core_reset(struct imx6_pcie *imx6_pcie)
{
	struct dw_pcie *pci = imx6_pcie->pci;
	struct device *dev = pci->dev;
	int ret;

	if (imx6_pcie->vpcie && !regulator_is_enabled(imx6_pcie->vpcie)) {
		ret = regulator_enable(imx6_pcie->vpcie);
		if (ret) {
			dev_err(dev, "failed to enable vpcie regulator: %d\n",
				ret);
			return;
		}
	}

	ret = clk_prepare_enable(imx6_pcie->pcie_phy);
	if (ret) {
		dev_err(dev, "unable to enable pcie_phy clock\n");
		goto err_pcie_phy;
	}

	ret = clk_prepare_enable(imx6_pcie->pcie_bus);
	if (ret) {
		dev_err(dev, "unable to enable pcie_bus clock\n");
		goto err_pcie_bus;
	}

	ret = clk_prepare_enable(imx6_pcie->pcie);
	if (ret) {
		dev_err(dev, "unable to enable pcie clock\n");
		goto err_pcie;
	}

	ret = imx6_pcie_enable_ref_clk(imx6_pcie);
	if (ret) {
		dev_err(dev, "unable to enable pcie ref clock\n");
		goto err_ref_clk;
	}

	/* allow the clocks to stabilize */
	usleep_range(200, 500);

	/* Some boards don't have PCIe reset GPIO. */
	if (gpio_is_valid(imx6_pcie->reset_gpio)) {
		gpio_set_value_cansleep(imx6_pcie->reset_gpio,
					imx6_pcie->gpio_active_high);
		msleep(100);
		gpio_set_value_cansleep(imx6_pcie->reset_gpio,
					!imx6_pcie->gpio_active_high);
	}

	switch (imx6_pcie->drvdata->variant) {
	case IMX8MQ:
		reset_control_deassert(imx6_pcie->pciephy_reset);
		break;
	case IMX7D:
		reset_control_deassert(imx6_pcie->pciephy_reset);

		/* Workaround for ERR010728, failure of PCI-e PLL VCO to
		 * oscillate, especially when cold.  This turns off "Duty-cycle
		 * Corrector" and other mysterious undocumented things.
		 */
		if (likely(imx6_pcie->phy_base)) {
			/* De-assert DCC_FB_EN */
			writel(PCIE_PHY_CMN_REG4_DCC_FB_EN,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_REG4);
			/* Assert RX_EQS and RX_EQS_SEL */
			writel(PCIE_PHY_CMN_REG24_RX_EQ_SEL
				| PCIE_PHY_CMN_REG24_RX_EQ,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_REG24);
			/* Assert ATT_MODE */
			writel(PCIE_PHY_CMN_REG26_ATT_MODE,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_REG26);
		} else {
			dev_warn(dev, "Unable to apply ERR010728 workaround. DT missing fsl,imx7d-pcie-phy phandle ?\n");
		}

		imx7d_pcie_wait_for_phy_pll_lock(imx6_pcie);
		break;
	case IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR5,
				   IMX6SX_GPR5_PCIE_BTNRST_RESET, 0);
		break;
	case IMX6QP:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_SW_RST, 0);

		usleep_range(200, 500);
		break;
	case IMX6Q:		/* Nothing to do */
		break;
	}

	return;

err_ref_clk:
	clk_disable_unprepare(imx6_pcie->pcie);
err_pcie:
	clk_disable_unprepare(imx6_pcie->pcie_bus);
err_pcie_bus:
	clk_disable_unprepare(imx6_pcie->pcie_phy);
err_pcie_phy:
	if (imx6_pcie->vpcie && regulator_is_enabled(imx6_pcie->vpcie) > 0) {
		ret = regulator_disable(imx6_pcie->vpcie);
		if (ret)
			dev_err(dev, "failed to disable vpcie regulator: %d\n",
				ret);
	}
}