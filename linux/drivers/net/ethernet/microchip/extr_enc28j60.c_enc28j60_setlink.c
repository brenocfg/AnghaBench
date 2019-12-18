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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct enc28j60_net {int full_duplex; int /*<<< orphan*/  hw_enable; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 scalar_t__ SPEED_10 ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ netif_msg_link (struct enc28j60_net*) ; 

__attribute__((used)) static int
enc28j60_setlink(struct net_device *ndev, u8 autoneg, u16 speed, u8 duplex)
{
	struct enc28j60_net *priv = netdev_priv(ndev);
	int ret = 0;

	if (!priv->hw_enable) {
		/* link is in low power mode now; duplex setting
		 * will take effect on next enc28j60_hw_init().
		 */
		if (autoneg == AUTONEG_DISABLE && speed == SPEED_10)
			priv->full_duplex = (duplex == DUPLEX_FULL);
		else {
			if (netif_msg_link(priv))
				netdev_warn(ndev, "unsupported link setting\n");
			ret = -EOPNOTSUPP;
		}
	} else {
		if (netif_msg_link(priv))
			netdev_warn(ndev, "Warning: hw must be disabled to set link mode\n");
		ret = -EBUSY;
	}
	return ret;
}