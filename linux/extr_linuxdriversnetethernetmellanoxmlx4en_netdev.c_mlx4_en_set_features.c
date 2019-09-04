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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  hwtstamp_config; int /*<<< orphan*/  port; TYPE_1__* mdev; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DEV_FEATURE_CHANGED (struct net_device*,int,int) ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_HW_VLAN_STAG_TX ; 
 int NETIF_F_LOOPBACK ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXFCS ; 
 int /*<<< orphan*/  en_info (struct mlx4_en_priv*,char*,char*) ; 
 int mlx4_SET_PORT_fcs_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx4_en_reset_config (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_en_update_loopback_state (struct net_device*,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_features(struct net_device *netdev,
		netdev_features_t features)
{
	struct mlx4_en_priv *priv = netdev_priv(netdev);
	bool reset = false;
	int ret = 0;

	if (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_RXFCS)) {
		en_info(priv, "Turn %s RX-FCS\n",
			(features & NETIF_F_RXFCS) ? "ON" : "OFF");
		reset = true;
	}

	if (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_RXALL)) {
		u8 ignore_fcs_value = (features & NETIF_F_RXALL) ? 1 : 0;

		en_info(priv, "Turn %s RX-ALL\n",
			ignore_fcs_value ? "ON" : "OFF");
		ret = mlx4_SET_PORT_fcs_check(priv->mdev->dev,
					      priv->port, ignore_fcs_value);
		if (ret)
			return ret;
	}

	if (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_HW_VLAN_CTAG_RX)) {
		en_info(priv, "Turn %s RX vlan strip offload\n",
			(features & NETIF_F_HW_VLAN_CTAG_RX) ? "ON" : "OFF");
		reset = true;
	}

	if (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_HW_VLAN_CTAG_TX))
		en_info(priv, "Turn %s TX vlan strip offload\n",
			(features & NETIF_F_HW_VLAN_CTAG_TX) ? "ON" : "OFF");

	if (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_HW_VLAN_STAG_TX))
		en_info(priv, "Turn %s TX S-VLAN strip offload\n",
			(features & NETIF_F_HW_VLAN_STAG_TX) ? "ON" : "OFF");

	if (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_LOOPBACK)) {
		en_info(priv, "Turn %s loopback\n",
			(features & NETIF_F_LOOPBACK) ? "ON" : "OFF");
		mlx4_en_update_loopback_state(netdev, features);
	}

	if (reset) {
		ret = mlx4_en_reset_config(netdev, priv->hwtstamp_config,
					   features);
		if (ret)
			return ret;
	}

	return 0;
}