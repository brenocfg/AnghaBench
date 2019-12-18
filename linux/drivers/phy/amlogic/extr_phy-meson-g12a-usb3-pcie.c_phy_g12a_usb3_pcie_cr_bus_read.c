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
 unsigned int FIELD_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PHY_R4 ; 
 int /*<<< orphan*/  PHY_R4_PHY_CR_READ ; 
 int /*<<< orphan*/  PHY_R5 ; 
 unsigned int PHY_R5_PHY_CR_ACK ; 
 int /*<<< orphan*/  PHY_R5_PHY_CR_DATA_OUT ; 
 int phy_g12a_usb3_pcie_cr_bus_addr (struct phy_g12a_usb3_pcie_priv*,unsigned int) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_g12a_usb3_pcie_cr_bus_read(void *context, unsigned int addr,
					  unsigned int *data)
{
	struct phy_g12a_usb3_pcie_priv *priv = context;
	unsigned int val;
	int ret;

	ret = phy_g12a_usb3_pcie_cr_bus_addr(priv, addr);
	if (ret)
		return ret;

	regmap_write(priv->regmap, PHY_R4, 0);
	regmap_write(priv->regmap, PHY_R4, PHY_R4_PHY_CR_READ);

	ret = regmap_read_poll_timeout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	if (ret)
		return ret;

	*data = FIELD_GET(PHY_R5_PHY_CR_DATA_OUT, val);

	regmap_write(priv->regmap, PHY_R4, 0);

	ret = regmap_read_poll_timeout(priv->regmap, PHY_R5, val,
				       !(val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	if (ret)
		return ret;

	return 0;
}