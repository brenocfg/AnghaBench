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
typedef  int /*<<< orphan*/  u16 ;
struct sxgbe_priv_data {int dummy; } ;
struct net_device {int dummy; } ;
struct mii_bus {struct net_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_SMA_WRITE_CMD ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int sxgbe_mdio_access (struct sxgbe_priv_data*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sxgbe_mdio_write(struct mii_bus *bus, int phyaddr, int phyreg,
			     u16 phydata)
{
	struct net_device *ndev = bus->priv;
	struct sxgbe_priv_data *priv = netdev_priv(ndev);

	return sxgbe_mdio_access(priv, SXGBE_SMA_WRITE_CMD, phyaddr, phyreg,
				 phydata);
}