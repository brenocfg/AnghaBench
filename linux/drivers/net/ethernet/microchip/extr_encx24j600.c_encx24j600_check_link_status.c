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
struct encx24j600_priv {scalar_t__ autoneg; int full_duplex; int /*<<< orphan*/  speed; struct net_device* ndev; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  ESTAT ; 
 int PHYLNK ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int encx24j600_read_reg (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_wait_for_autoneg (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct encx24j600_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static void encx24j600_check_link_status(struct encx24j600_priv *priv)
{
	struct net_device *dev = priv->ndev;
	u16 estat;

	estat = encx24j600_read_reg(priv, ESTAT);

	if (estat & PHYLNK) {
		if (priv->autoneg == AUTONEG_ENABLE)
			encx24j600_wait_for_autoneg(priv);

		netif_carrier_on(dev);
		netif_info(priv, ifup, dev, "link up\n");
	} else {
		netif_info(priv, ifdown, dev, "link down\n");

		/* Re-enable autoneg since we won't know what we might be
		 * connected to when the link is brought back up again.
		 */
		priv->autoneg  = AUTONEG_ENABLE;
		priv->full_duplex = true;
		priv->speed = SPEED_100;
		netif_carrier_off(dev);
	}
}