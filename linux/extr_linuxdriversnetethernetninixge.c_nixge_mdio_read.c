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
typedef  int u16 ;
struct nixge_priv {int /*<<< orphan*/  dev; } ;
struct mii_bus {struct nixge_priv* priv; } ;

/* Variables and functions */
 int MII_ADDR_C45 ; 
 int NIXGE_MDIO_ADDR (int) ; 
 int /*<<< orphan*/  NIXGE_MDIO_C22_READ ; 
 int /*<<< orphan*/  NIXGE_MDIO_C45_READ ; 
 int NIXGE_MDIO_CLAUSE22 ; 
 int NIXGE_MDIO_CLAUSE45 ; 
 int NIXGE_MDIO_MMD (int) ; 
 int NIXGE_MDIO_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIXGE_MDIO_OP_ADDRESS ; 
 int /*<<< orphan*/  NIXGE_REG_MDIO_ADDR ; 
 int /*<<< orphan*/  NIXGE_REG_MDIO_CTRL ; 
 int /*<<< orphan*/  NIXGE_REG_MDIO_DATA ; 
 int /*<<< orphan*/  NIXGE_REG_MDIO_OP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int nixge_ctrl_poll_timeout (struct nixge_priv*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int nixge_ctrl_read_reg (struct nixge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_ctrl_write_reg (struct nixge_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nixge_mdio_read(struct mii_bus *bus, int phy_id, int reg)
{
	struct nixge_priv *priv = bus->priv;
	u32 status, tmp;
	int err;
	u16 device;

	if (reg & MII_ADDR_C45) {
		device = (reg >> 16) & 0x1f;

		nixge_ctrl_write_reg(priv, NIXGE_REG_MDIO_ADDR, reg & 0xffff);

		tmp = NIXGE_MDIO_CLAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_OP_ADDRESS)
			| NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);

		nixge_ctrl_write_reg(priv, NIXGE_REG_MDIO_OP, tmp);
		nixge_ctrl_write_reg(priv, NIXGE_REG_MDIO_CTRL, 1);

		err = nixge_ctrl_poll_timeout(priv, NIXGE_REG_MDIO_CTRL, status,
					      !status, 10, 1000);
		if (err) {
			dev_err(priv->dev, "timeout setting address");
			return err;
		}

		tmp = NIXGE_MDIO_CLAUSE45 | NIXGE_MDIO_OP(NIXGE_MDIO_C45_READ) |
			NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);
	} else {
		device = reg & 0x1f;

		tmp = NIXGE_MDIO_CLAUSE22 | NIXGE_MDIO_OP(NIXGE_MDIO_C22_READ) |
			NIXGE_MDIO_ADDR(phy_id) | NIXGE_MDIO_MMD(device);
	}

	nixge_ctrl_write_reg(priv, NIXGE_REG_MDIO_OP, tmp);
	nixge_ctrl_write_reg(priv, NIXGE_REG_MDIO_CTRL, 1);

	err = nixge_ctrl_poll_timeout(priv, NIXGE_REG_MDIO_CTRL, status,
				      !status, 10, 1000);
	if (err) {
		dev_err(priv->dev, "timeout setting read command");
		return err;
	}

	status = nixge_ctrl_read_reg(priv, NIXGE_REG_MDIO_DATA);

	return status;
}