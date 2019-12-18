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
typedef  int /*<<< orphan*/  u16 ;
struct xlr_net_priv {TYPE_1__* ndev; int /*<<< orphan*/  mii_addr; } ;
struct mii_bus {struct xlr_net_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int xlr_phy_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlr_mii_write(struct mii_bus *bus, int phy_addr, int regnum, u16 val)
{
	struct xlr_net_priv *priv = bus->priv;
	int ret;

	ret = xlr_phy_write(priv->mii_addr, phy_addr, regnum, val);
	dev_dbg(&priv->ndev->dev, "mii_write phy %d : %d <- %x [%x]\n",
		phy_addr, regnum, val, ret);
	return ret;
}