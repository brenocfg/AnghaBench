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
typedef  int u8 ;
typedef  int u32 ;
struct xgene_mdio_pdata {int dummy; } ;
struct mii_bus {int /*<<< orphan*/  dev; scalar_t__ priv; } ;

/* Variables and functions */
 int BUSY_MASK ; 
 int EBUSY ; 
 int /*<<< orphan*/  MII_MGMT_ADDRESS_ADDR ; 
 int /*<<< orphan*/  MII_MGMT_COMMAND_ADDR ; 
 int /*<<< orphan*/  MII_MGMT_INDICATORS_ADDR ; 
 int /*<<< orphan*/  MII_MGMT_STATUS_ADDR ; 
 int /*<<< orphan*/  PHY_ADDR ; 
 int READ_CYCLE_MASK ; 
 int /*<<< orphan*/  REG_ADDR ; 
 int SET_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xgene_mdio_rd_mac (struct xgene_mdio_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_mdio_wr_mac (struct xgene_mdio_pdata*,int /*<<< orphan*/ ,int) ; 

int xgene_mdio_rgmii_read(struct mii_bus *bus, int phy_id, int reg)
{
	struct xgene_mdio_pdata *pdata = (struct xgene_mdio_pdata *)bus->priv;
	u32 data, done;
	u8 wait = 10;

	data = SET_VAL(PHY_ADDR, phy_id) | SET_VAL(REG_ADDR, reg);
	xgene_mdio_wr_mac(pdata, MII_MGMT_ADDRESS_ADDR, data);
	xgene_mdio_wr_mac(pdata, MII_MGMT_COMMAND_ADDR, READ_CYCLE_MASK);
	do {
		usleep_range(5, 10);
		done = xgene_mdio_rd_mac(pdata, MII_MGMT_INDICATORS_ADDR);
	} while ((done & BUSY_MASK) && wait--);

	if (done & BUSY_MASK) {
		dev_err(&bus->dev, "MII_MGMT read failed\n");
		return -EBUSY;
	}

	data = xgene_mdio_rd_mac(pdata, MII_MGMT_STATUS_ADDR);
	xgene_mdio_wr_mac(pdata, MII_MGMT_COMMAND_ADDR, 0);

	return data;
}