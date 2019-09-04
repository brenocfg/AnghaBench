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
typedef  int u32 ;
struct TYPE_2__ {int ctrl; } ;
struct nfp_net {int cap; TYPE_1__ dp; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  NFP_NET_CFG_CTRL ; 
 int NFP_NET_CFG_CTRL_CTAG_FILTER ; 
 int NFP_NET_CFG_CTRL_GATHER ; 
 int NFP_NET_CFG_CTRL_LSO ; 
 int NFP_NET_CFG_CTRL_LSO2 ; 
 int NFP_NET_CFG_CTRL_LSO_ANY ; 
 int NFP_NET_CFG_CTRL_RXCSUM_ANY ; 
 int NFP_NET_CFG_CTRL_RXVLAN ; 
 int NFP_NET_CFG_CTRL_TXCSUM ; 
 int NFP_NET_CFG_CTRL_TXVLAN ; 
 int /*<<< orphan*/  NFP_NET_CFG_UPDATE_GEN ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 int nfp_net_reconfig (struct nfp_net*,int /*<<< orphan*/ ) ; 
 int nfp_port_set_features (struct net_device*,int) ; 
 int /*<<< orphan*/  nn_dbg (struct nfp_net*,char*,int,int,...) ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfp_net_set_features(struct net_device *netdev,
				netdev_features_t features)
{
	netdev_features_t changed = netdev->features ^ features;
	struct nfp_net *nn = netdev_priv(netdev);
	u32 new_ctrl;
	int err;

	/* Assume this is not called with features we have not advertised */

	new_ctrl = nn->dp.ctrl;

	if (changed & NETIF_F_RXCSUM) {
		if (features & NETIF_F_RXCSUM)
			new_ctrl |= nn->cap & NFP_NET_CFG_CTRL_RXCSUM_ANY;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_RXCSUM_ANY;
	}

	if (changed & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) {
		if (features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
			new_ctrl |= NFP_NET_CFG_CTRL_TXCSUM;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_TXCSUM;
	}

	if (changed & (NETIF_F_TSO | NETIF_F_TSO6)) {
		if (features & (NETIF_F_TSO | NETIF_F_TSO6))
			new_ctrl |= nn->cap & NFP_NET_CFG_CTRL_LSO2 ?:
					      NFP_NET_CFG_CTRL_LSO;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_LSO_ANY;
	}

	if (changed & NETIF_F_HW_VLAN_CTAG_RX) {
		if (features & NETIF_F_HW_VLAN_CTAG_RX)
			new_ctrl |= NFP_NET_CFG_CTRL_RXVLAN;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_RXVLAN;
	}

	if (changed & NETIF_F_HW_VLAN_CTAG_TX) {
		if (features & NETIF_F_HW_VLAN_CTAG_TX)
			new_ctrl |= NFP_NET_CFG_CTRL_TXVLAN;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_TXVLAN;
	}

	if (changed & NETIF_F_HW_VLAN_CTAG_FILTER) {
		if (features & NETIF_F_HW_VLAN_CTAG_FILTER)
			new_ctrl |= NFP_NET_CFG_CTRL_CTAG_FILTER;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_CTAG_FILTER;
	}

	if (changed & NETIF_F_SG) {
		if (features & NETIF_F_SG)
			new_ctrl |= NFP_NET_CFG_CTRL_GATHER;
		else
			new_ctrl &= ~NFP_NET_CFG_CTRL_GATHER;
	}

	err = nfp_port_set_features(netdev, features);
	if (err)
		return err;

	nn_dbg(nn, "Feature change 0x%llx -> 0x%llx (changed=0x%llx)\n",
	       netdev->features, features, changed);

	if (new_ctrl == nn->dp.ctrl)
		return 0;

	nn_dbg(nn, "NIC ctrl: 0x%x -> 0x%x\n", nn->dp.ctrl, new_ctrl);
	nn_writel(nn, NFP_NET_CFG_CTRL, new_ctrl);
	err = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	if (err)
		return err;

	nn->dp.ctrl = new_ctrl;

	return 0;
}