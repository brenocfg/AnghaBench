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
struct device {int dummy; } ;
struct ahci_host_priv {scalar_t__ mmio; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 scalar_t__ AHCI_DM816_P0PHYCR_REG ; 
 scalar_t__ AHCI_DM816_P1PHYCR_REG ; 
 int AHCI_DM816_PHY_ENPLL (int) ; 
 int AHCI_DM816_PHY_LOS (int) ; 
 int AHCI_DM816_PHY_MPY (int) ; 
 int AHCI_DM816_PHY_RXCDR (int) ; 
 int AHCI_DM816_PHY_RXEQ (int) ; 
 int AHCI_DM816_PHY_TXSWING (int) ; 
 int EINVAL ; 
 int ahci_dm816_get_mpy_bits (unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ahci_dm816_phy_init(struct ahci_host_priv *hpriv, struct device *dev)
{
	unsigned long refclk_rate;
	int mpy;
	u32 val;

	/*
	 * We should have been supplied two clocks: the functional and
	 * keep-alive clock and the external reference clock. We need the
	 * rate of the latter to calculate the correct value of MPY bits.
	 */
	if (!hpriv->clks[1]) {
		dev_err(dev, "reference clock not supplied\n");
		return -EINVAL;
	}

	refclk_rate = clk_get_rate(hpriv->clks[1]);
	if ((refclk_rate % 100) != 0) {
		dev_err(dev, "reference clock rate must be divisible by 100\n");
		return -EINVAL;
	}

	mpy = ahci_dm816_get_mpy_bits(refclk_rate);
	if (mpy < 0) {
		dev_err(dev, "can't calculate the MPY bits value\n");
		return -EINVAL;
	}

	/* Enable the PHY and configure the first HBA port. */
	val = AHCI_DM816_PHY_MPY(mpy) | AHCI_DM816_PHY_LOS(1) |
	      AHCI_DM816_PHY_RXCDR(4) | AHCI_DM816_PHY_RXEQ(1) |
	      AHCI_DM816_PHY_TXSWING(3) | AHCI_DM816_PHY_ENPLL(1);
	writel(val, hpriv->mmio + AHCI_DM816_P0PHYCR_REG);

	/* Configure the second HBA port. */
	val = AHCI_DM816_PHY_LOS(1) | AHCI_DM816_PHY_RXCDR(4) |
	      AHCI_DM816_PHY_RXEQ(1) | AHCI_DM816_PHY_TXSWING(3);
	writel(val, hpriv->mmio + AHCI_DM816_P1PHYCR_REG);

	return 0;
}