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
struct xgbe_hw_if {int (* enable_rss ) (struct xgbe_prv_data*) ;int (* disable_rss ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* disable_rx_vlan_filtering ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_rx_vlan_filtering ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* disable_rx_vlan_stripping ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_rx_vlan_stripping ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* disable_rx_csum ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* enable_rx_csum ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int netdev_features; struct xgbe_hw_if hw_if; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int stub1 (struct xgbe_prv_data*) ; 
 int stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub5 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub6 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub7 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub8 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_disable_vxlan_accel (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_vxlan_accel (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_set_features(struct net_device *netdev,
			     netdev_features_t features)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	netdev_features_t rxhash, rxcsum, rxvlan, rxvlan_filter;
	netdev_features_t udp_tunnel;
	int ret = 0;

	rxhash = pdata->netdev_features & NETIF_F_RXHASH;
	rxcsum = pdata->netdev_features & NETIF_F_RXCSUM;
	rxvlan = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_RX;
	rxvlan_filter = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_FILTER;
	udp_tunnel = pdata->netdev_features & NETIF_F_GSO_UDP_TUNNEL;

	if ((features & NETIF_F_RXHASH) && !rxhash)
		ret = hw_if->enable_rss(pdata);
	else if (!(features & NETIF_F_RXHASH) && rxhash)
		ret = hw_if->disable_rss(pdata);
	if (ret)
		return ret;

	if ((features & NETIF_F_RXCSUM) && !rxcsum)
		hw_if->enable_rx_csum(pdata);
	else if (!(features & NETIF_F_RXCSUM) && rxcsum)
		hw_if->disable_rx_csum(pdata);

	if ((features & NETIF_F_HW_VLAN_CTAG_RX) && !rxvlan)
		hw_if->enable_rx_vlan_stripping(pdata);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_RX) && rxvlan)
		hw_if->disable_rx_vlan_stripping(pdata);

	if ((features & NETIF_F_HW_VLAN_CTAG_FILTER) && !rxvlan_filter)
		hw_if->enable_rx_vlan_filtering(pdata);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) && rxvlan_filter)
		hw_if->disable_rx_vlan_filtering(pdata);

	if ((features & NETIF_F_GSO_UDP_TUNNEL) && !udp_tunnel)
		xgbe_enable_vxlan_accel(pdata);
	else if (!(features & NETIF_F_GSO_UDP_TUNNEL) && udp_tunnel)
		xgbe_disable_vxlan_accel(pdata);

	pdata->netdev_features = features;

	DBGPR("<--xgbe_set_features\n");

	return 0;
}