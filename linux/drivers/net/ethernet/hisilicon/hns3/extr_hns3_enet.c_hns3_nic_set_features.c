#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int features; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_gro_en ) (struct hnae3_handle*,int) ;int (* enable_hw_strip_rxvtag ) (struct hnae3_handle*,int) ;int /*<<< orphan*/  (* enable_fd ) (struct hnae3_handle*,int) ;int /*<<< orphan*/  (* enable_vlan_filter ) (struct hnae3_handle*,int) ;} ;

/* Variables and functions */
 int NETIF_F_GRO_HW ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_NTUPLE ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int) ; 
 int stub3 (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  stub4 (struct hnae3_handle*,int) ; 

__attribute__((used)) static int hns3_nic_set_features(struct net_device *netdev,
				 netdev_features_t features)
{
	netdev_features_t changed = netdev->features ^ features;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	bool enable;
	int ret;

	if (changed & (NETIF_F_GRO_HW) && h->ae_algo->ops->set_gro_en) {
		enable = !!(features & NETIF_F_GRO_HW);
		ret = h->ae_algo->ops->set_gro_en(h, enable);
		if (ret)
			return ret;
	}

	if ((changed & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    h->ae_algo->ops->enable_vlan_filter) {
		enable = !!(features & NETIF_F_HW_VLAN_CTAG_FILTER);
		h->ae_algo->ops->enable_vlan_filter(h, enable);
	}

	if ((changed & NETIF_F_HW_VLAN_CTAG_RX) &&
	    h->ae_algo->ops->enable_hw_strip_rxvtag) {
		enable = !!(features & NETIF_F_HW_VLAN_CTAG_RX);
		ret = h->ae_algo->ops->enable_hw_strip_rxvtag(h, enable);
		if (ret)
			return ret;
	}

	if ((changed & NETIF_F_NTUPLE) && h->ae_algo->ops->enable_fd) {
		enable = !!(features & NETIF_F_NTUPLE);
		h->ae_algo->ops->enable_fd(h, enable);
	}

	netdev->features = features;
	return 0;
}