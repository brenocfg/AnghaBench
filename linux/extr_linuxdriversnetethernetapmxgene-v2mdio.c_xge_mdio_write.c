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
typedef  int u16 ;
struct xge_pdata {int dummy; } ;
struct mii_bus {int /*<<< orphan*/  dev; struct xge_pdata* priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MII_MGMT_ADDRESS ; 
 int MII_MGMT_BUSY ; 
 int /*<<< orphan*/  MII_MGMT_CONTROL ; 
 int /*<<< orphan*/  MII_MGMT_INDICATORS ; 
 int /*<<< orphan*/  PHY_ADDR ; 
 int /*<<< orphan*/  REG_ADDR ; 
 int /*<<< orphan*/  SET_REG_BITS (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xge_mdio_write(struct mii_bus *bus, int phy_id, int reg, u16 data)
{
	struct xge_pdata *pdata = bus->priv;
	u32 done, val = 0;
	u8 wait = 10;

	SET_REG_BITS(&val, PHY_ADDR, phy_id);
	SET_REG_BITS(&val, REG_ADDR, reg);
	xge_wr_csr(pdata, MII_MGMT_ADDRESS, val);

	xge_wr_csr(pdata, MII_MGMT_CONTROL, data);
	do {
		usleep_range(5, 10);
		done = xge_rd_csr(pdata, MII_MGMT_INDICATORS);
	} while ((done & MII_MGMT_BUSY) && wait--);

	if (done & MII_MGMT_BUSY) {
		dev_err(&bus->dev, "MII_MGMT write failed\n");
		return -ETIMEDOUT;
	}

	return 0;
}