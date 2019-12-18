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
struct net_device {scalar_t__ mtu; } ;
struct TYPE_2__ {scalar_t__ max_mtu; int /*<<< orphan*/  mac_addr; } ;
struct ena_com_dev_get_features_ctx {TYPE_1__ dev_attr; } ;
struct ena_adapter {int /*<<< orphan*/  mac_addr; struct net_device* netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static int ena_device_validate_params(struct ena_adapter *adapter,
				      struct ena_com_dev_get_features_ctx *get_feat_ctx)
{
	struct net_device *netdev = adapter->netdev;
	int rc;

	rc = ether_addr_equal(get_feat_ctx->dev_attr.mac_addr,
			      adapter->mac_addr);
	if (!rc) {
		netif_err(adapter, drv, netdev,
			  "Error, mac address are different\n");
		return -EINVAL;
	}

	if (get_feat_ctx->dev_attr.max_mtu < netdev->mtu) {
		netif_err(adapter, drv, netdev,
			  "Error, device max mtu is smaller than netdev MTU\n");
		return -EINVAL;
	}

	return 0;
}