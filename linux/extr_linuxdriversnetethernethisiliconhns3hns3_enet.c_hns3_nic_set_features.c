#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int features; } ;
struct TYPE_4__ {int /*<<< orphan*/  maybe_stop_tx; int /*<<< orphan*/  fill_desc; } ;
struct hns3_nic_priv {TYPE_1__ ops; struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_3__* ae_algo; } ;
typedef  int netdev_features_t ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int (* enable_hw_strip_rxvtag ) (struct hnae3_handle*,int) ;int /*<<< orphan*/  (* enable_vlan_filter ) (struct hnae3_handle*,int) ;} ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  hns3_fill_desc ; 
 int /*<<< orphan*/  hns3_fill_desc_tso ; 
 int /*<<< orphan*/  hns3_nic_maybe_stop_tso ; 
 int /*<<< orphan*/  hns3_nic_maybe_stop_tx ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int) ; 
 int stub3 (struct hnae3_handle*,int) ; 
 int stub4 (struct hnae3_handle*,int) ; 

__attribute__((used)) static int hns3_nic_set_features(struct net_device *netdev,
				 netdev_features_t features)
{
	netdev_features_t changed = netdev->features ^ features;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	int ret;

	if (changed & (NETIF_F_TSO | NETIF_F_TSO6)) {
		if (features & (NETIF_F_TSO | NETIF_F_TSO6)) {
			priv->ops.fill_desc = hns3_fill_desc_tso;
			priv->ops.maybe_stop_tx = hns3_nic_maybe_stop_tso;
		} else {
			priv->ops.fill_desc = hns3_fill_desc;
			priv->ops.maybe_stop_tx = hns3_nic_maybe_stop_tx;
		}
	}

	if ((changed & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    h->ae_algo->ops->enable_vlan_filter) {
		if (features & NETIF_F_HW_VLAN_CTAG_FILTER)
			h->ae_algo->ops->enable_vlan_filter(h, true);
		else
			h->ae_algo->ops->enable_vlan_filter(h, false);
	}

	if ((changed & NETIF_F_HW_VLAN_CTAG_RX) &&
	    h->ae_algo->ops->enable_hw_strip_rxvtag) {
		if (features & NETIF_F_HW_VLAN_CTAG_RX)
			ret = h->ae_algo->ops->enable_hw_strip_rxvtag(h, true);
		else
			ret = h->ae_algo->ops->enable_hw_strip_rxvtag(h, false);

		if (ret)
			return ret;
	}

	netdev->features = features;
	return 0;
}