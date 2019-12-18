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
struct phy_g12a_usb3_pcie_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PHY_R4 ; 
 unsigned int PHY_R4_PHY_CR_CAP_ADDR ; 
 int /*<<< orphan*/  PHY_R4_PHY_CR_DATA_IN ; 
 int /*<<< orphan*/  PHY_R5 ; 
 unsigned int PHY_R5_PHY_CR_ACK ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int phy_g12a_usb3_pcie_cr_bus_addr(struct phy_g12a_usb3_pcie_priv *priv,
					  unsigned int addr)
{
	unsigned int val, reg;
	int ret;

	reg = FIELD_PREP(PHY_R4_PHY_CR_DATA_IN, addr);

	regmap_write(priv->regmap, PHY_R4, reg);
	regmap_write(priv->regmap, PHY_R4, reg);

	regmap_write(priv->regmap, PHY_R4, reg | PHY_R4_PHY_CR_CAP_ADDR);

	ret = regmap_read_poll_timeout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	if (ret)
		return ret;

	regmap_write(priv->regmap, PHY_R4, reg);

	ret = regmap_read_poll_timeout(priv->regmap, PHY_R5, val,
				       !(val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	if (ret)
		return ret;

	return 0;
}