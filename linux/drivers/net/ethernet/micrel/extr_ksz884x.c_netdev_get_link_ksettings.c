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
struct TYPE_2__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;
struct dev_priv {int /*<<< orphan*/  advertising; int /*<<< orphan*/  mii_if; struct dev_info* adapter; } ;
struct dev_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_get_link_ksettings(struct net_device *dev,
				     struct ethtool_link_ksettings *cmd)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	mutex_lock(&hw_priv->lock);
	mii_ethtool_get_link_ksettings(&priv->mii_if, cmd);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, TP);
	mutex_unlock(&hw_priv->lock);

	/* Save advertised settings for workaround in next function. */
	ethtool_convert_link_mode_to_legacy_u32(&priv->advertising,
						cmd->link_modes.advertising);

	return 0;
}