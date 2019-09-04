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
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct altera_tse_private {scalar_t__ phy_addr; TYPE_1__* device; int /*<<< orphan*/  phy_iface; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ PHY_MAX_ADDR ; 
 scalar_t__ POLL_PHY ; 
 int altera_tse_mdio_create (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instance_count ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_get_phy_mode (struct device_node*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int altera_tse_phy_get_addr_mdio_create(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	struct device_node *np = priv->device->of_node;
	int ret = 0;

	priv->phy_iface = of_get_phy_mode(np);

	/* Avoid get phy addr and create mdio if no phy is present */
	if (!priv->phy_iface)
		return 0;

	/* try to get PHY address from device tree, use PHY autodetection if
	 * no valid address is given
	 */

	if (of_property_read_u32(priv->device->of_node, "phy-addr",
			 &priv->phy_addr)) {
		priv->phy_addr = POLL_PHY;
	}

	if (!((priv->phy_addr == POLL_PHY) ||
		  ((priv->phy_addr >= 0) && (priv->phy_addr < PHY_MAX_ADDR)))) {
		netdev_err(dev, "invalid phy-addr specified %d\n",
			priv->phy_addr);
		return -ENODEV;
	}

	/* Create/attach to MDIO bus */
	ret = altera_tse_mdio_create(dev,
					 atomic_add_return(1, &instance_count));

	if (ret)
		return -ENODEV;

	return 0;
}