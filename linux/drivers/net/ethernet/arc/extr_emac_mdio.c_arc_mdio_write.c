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
typedef  int u16 ;
struct mii_bus {struct arc_emac_priv* priv; } ;
struct arc_emac_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_MDIO ; 
 int arc_mdio_complete_wait (struct arc_emac_priv*) ; 
 int /*<<< orphan*/  arc_reg_set (struct arc_emac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int arc_mdio_write(struct mii_bus *bus, int phy_addr,
			  int reg_num, u16 value)
{
	struct arc_emac_priv *priv = bus->priv;

	dev_dbg(priv->dev,
		"arc_mdio_write(phy_addr=%i, reg_num=%x, value=%x)\n",
		phy_addr, reg_num, value);

	arc_reg_set(priv, R_MDIO,
		    0x50020000 | (phy_addr << 23) | (reg_num << 18) | value);

	return arc_mdio_complete_wait(priv);
}