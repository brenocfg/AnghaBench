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
typedef  int u32 ;
struct kirin_pcie {TYPE_1__* pci; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCIE_APB_PHY_CTRL0 ; 
 int /*<<< orphan*/  PCIE_APB_PHY_CTRL1 ; 
 int /*<<< orphan*/  PCIE_APB_PHY_STATUS0 ; 
 int PHY_PWR_DOWN_BIT ; 
 int PHY_REF_PAD_BIT ; 
 int PHY_RST_ACK_BIT ; 
 int PIPE_CLK_STABLE ; 
 int /*<<< orphan*/  PIPE_CLK_WAIT_MAX ; 
 int /*<<< orphan*/  PIPE_CLK_WAIT_MIN ; 
 int /*<<< orphan*/  TIME_PHY_PD_MAX ; 
 int /*<<< orphan*/  TIME_PHY_PD_MIN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int kirin_apb_phy_readl (struct kirin_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kirin_apb_phy_writel (struct kirin_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kirin_pcie_phy_init(struct kirin_pcie *kirin_pcie)
{
	struct device *dev = kirin_pcie->pci->dev;
	u32 reg_val;

	reg_val = kirin_apb_phy_readl(kirin_pcie, PCIE_APB_PHY_CTRL1);
	reg_val &= ~PHY_REF_PAD_BIT;
	kirin_apb_phy_writel(kirin_pcie, reg_val, PCIE_APB_PHY_CTRL1);

	reg_val = kirin_apb_phy_readl(kirin_pcie, PCIE_APB_PHY_CTRL0);
	reg_val &= ~PHY_PWR_DOWN_BIT;
	kirin_apb_phy_writel(kirin_pcie, reg_val, PCIE_APB_PHY_CTRL0);
	usleep_range(TIME_PHY_PD_MIN, TIME_PHY_PD_MAX);

	reg_val = kirin_apb_phy_readl(kirin_pcie, PCIE_APB_PHY_CTRL1);
	reg_val &= ~PHY_RST_ACK_BIT;
	kirin_apb_phy_writel(kirin_pcie, reg_val, PCIE_APB_PHY_CTRL1);

	usleep_range(PIPE_CLK_WAIT_MIN, PIPE_CLK_WAIT_MAX);
	reg_val = kirin_apb_phy_readl(kirin_pcie, PCIE_APB_PHY_STATUS0);
	if (reg_val & PIPE_CLK_STABLE) {
		dev_err(dev, "PIPE clk is not stable\n");
		return -EINVAL;
	}

	return 0;
}