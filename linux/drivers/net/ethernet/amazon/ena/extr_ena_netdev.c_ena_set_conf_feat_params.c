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
struct net_device {int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mac_addr; } ;
struct ena_com_dev_get_features_ctx {TYPE_1__ dev_attr; } ;
struct ena_adapter {int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mac_addr; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_MIN_MTU ; 
 int /*<<< orphan*/  ena_set_dev_offloads (struct ena_com_dev_get_features_ctx*,struct net_device*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_set_conf_feat_params(struct ena_adapter *adapter,
				     struct ena_com_dev_get_features_ctx *feat)
{
	struct net_device *netdev = adapter->netdev;

	/* Copy mac address */
	if (!is_valid_ether_addr(feat->dev_attr.mac_addr)) {
		eth_hw_addr_random(netdev);
		ether_addr_copy(adapter->mac_addr, netdev->dev_addr);
	} else {
		ether_addr_copy(adapter->mac_addr, feat->dev_attr.mac_addr);
		ether_addr_copy(netdev->dev_addr, adapter->mac_addr);
	}

	/* Set offload features */
	ena_set_dev_offloads(feat, netdev);

	adapter->max_mtu = feat->dev_attr.max_mtu;
	netdev->max_mtu = adapter->max_mtu;
	netdev->min_mtu = ENA_MIN_MTU;
}