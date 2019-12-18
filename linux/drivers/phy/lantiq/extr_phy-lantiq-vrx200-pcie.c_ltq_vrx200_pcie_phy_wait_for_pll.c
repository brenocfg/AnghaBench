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
struct phy {int dummy; } ;
struct ltq_vrx200_pcie_phy_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PHY_PLL_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct ltq_vrx200_pcie_phy_priv* phy_get_drvdata (struct phy*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 

__attribute__((used)) static int ltq_vrx200_pcie_phy_wait_for_pll(struct phy *phy)
{
	struct ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	unsigned int tmp;
	int ret;

	ret = regmap_read_poll_timeout(priv->phy_regmap, PCIE_PHY_PLL_STATUS,
				       tmp, ((tmp & 0x0070) == 0x0070), 10,
				       10000);
	if (ret) {
		dev_err(priv->dev, "PLL Link timeout, PLL status = 0x%04x\n",
			tmp);
		return ret;
	}

	return 0;
}