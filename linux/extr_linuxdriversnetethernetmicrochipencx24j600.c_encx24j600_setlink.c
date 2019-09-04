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
struct encx24j600_priv {int autoneg; int full_duplex; int speed; int /*<<< orphan*/  hw_enabled; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  link ; 
 struct encx24j600_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct encx24j600_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static int encx24j600_setlink(struct net_device *dev, u8 autoneg, u16 speed,
			      u8 duplex)
{
	struct encx24j600_priv *priv = netdev_priv(dev);
	int ret = 0;

	if (!priv->hw_enabled) {
		/* link is in low power mode now; duplex setting
		 * will take effect on next encx24j600_hw_init()
		 */
		if (speed == SPEED_10 || speed == SPEED_100) {
			priv->autoneg = (autoneg == AUTONEG_ENABLE);
			priv->full_duplex = (duplex == DUPLEX_FULL);
			priv->speed = (speed == SPEED_100);
		} else {
			netif_warn(priv, link, dev, "unsupported link speed setting\n");
			/*speeds other than SPEED_10 and SPEED_100 */
			/*are not supported by chip */
			ret = -EOPNOTSUPP;
		}
	} else {
		netif_warn(priv, link, dev, "Warning: hw must be disabled to set link mode\n");
		ret = -EBUSY;
	}
	return ret;
}