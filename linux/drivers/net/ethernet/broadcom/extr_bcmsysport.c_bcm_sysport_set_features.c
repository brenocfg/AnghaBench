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
struct net_device {int dummy; } ;
struct bcm_sysport_priv {int crc_fwd; int /*<<< orphan*/  is_lite; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int CMD_CRC_FWD ; 
 int /*<<< orphan*/  GIB_CONTROL ; 
 int GIB_FCS_STRIP ; 
 int GIB_FCS_STRIP_SHIFT ; 
 int /*<<< orphan*/  UMAC_CMD ; 
 int /*<<< orphan*/  bcm_sysport_set_rx_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sysport_set_tx_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 int gib_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int umac_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sysport_set_features(struct net_device *dev,
				    netdev_features_t features)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);

	/* Read CRC forward */
	if (!priv->is_lite)
		priv->crc_fwd = !!(umac_readl(priv, UMAC_CMD) & CMD_CRC_FWD);
	else
		priv->crc_fwd = !((gib_readl(priv, GIB_CONTROL) &
				  GIB_FCS_STRIP) >> GIB_FCS_STRIP_SHIFT);

	bcm_sysport_set_rx_csum(dev, features);
	bcm_sysport_set_tx_csum(dev, features);

	return 0;
}