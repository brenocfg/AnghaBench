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
struct net_device {int dummy; } ;
struct mii_bus {struct net_device* priv; } ;
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  csrwr32 (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdio_phy1 ; 
 int /*<<< orphan*/  mdio_phy1_addr ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 scalar_t__ tse_csroffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_tse_mdio_write(struct mii_bus *bus, int mii_id, int regnum,
				 u16 value)
{
	struct net_device *ndev = bus->priv;
	struct altera_tse_private *priv = netdev_priv(ndev);

	/* set MDIO address */
	csrwr32((mii_id & 0x1f), priv->mac_dev,
		tse_csroffs(mdio_phy1_addr));

	/* write the data */
	csrwr32(value, priv->mac_dev, tse_csroffs(mdio_phy1) + regnum * 4);
	return 0;
}