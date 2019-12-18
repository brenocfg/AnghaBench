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
struct net_device {int flags; } ;
struct altera_tse_private {int /*<<< orphan*/  mac_cfg_lock; int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MAC_CMDCFG_PROMIS_EN ; 
 int /*<<< orphan*/  command_config ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_uc_empty (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tse_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tse_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tse_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tse_set_rx_mode(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);

	spin_lock(&priv->mac_cfg_lock);

	if ((dev->flags & IFF_PROMISC) || (dev->flags & IFF_ALLMULTI) ||
	    !netdev_mc_empty(dev) || !netdev_uc_empty(dev))
		tse_set_bit(priv->mac_dev, tse_csroffs(command_config),
			    MAC_CMDCFG_PROMIS_EN);
	else
		tse_clear_bit(priv->mac_dev, tse_csroffs(command_config),
			      MAC_CMDCFG_PROMIS_EN);

	spin_unlock(&priv->mac_cfg_lock);
}