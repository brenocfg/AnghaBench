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
struct net_device {int /*<<< orphan*/  dev; } ;
struct mvneta_port {int /*<<< orphan*/  phylink; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_set_wol (int /*<<< orphan*/ ,struct ethtool_wolinfo*) ; 

__attribute__((used)) static int mvneta_ethtool_set_wol(struct net_device *dev,
				  struct ethtool_wolinfo *wol)
{
	struct mvneta_port *pp = netdev_priv(dev);
	int ret;

	ret = phylink_ethtool_set_wol(pp->phylink, wol);
	if (!ret)
		device_set_wakeup_enable(&dev->dev, !!wol->wolopts);

	return ret;
}