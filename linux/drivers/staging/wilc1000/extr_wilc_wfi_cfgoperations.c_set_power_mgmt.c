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
struct wiphy {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  hif_drv; } ;
struct wilc_vif {struct wilc_priv priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wilc_set_power_mgmt (struct wilc_vif*,int,int) ; 

__attribute__((used)) static int set_power_mgmt(struct wiphy *wiphy, struct net_device *dev,
			  bool enabled, int timeout)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc_priv *priv = &vif->priv;

	if (!priv->hif_drv)
		return -EIO;

	wilc_set_power_mgmt(vif, enabled, timeout);

	return 0;
}