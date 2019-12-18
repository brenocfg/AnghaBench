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
struct net_device {int dummy; } ;
struct hns3_nic_priv {TYPE_2__* ring_data; struct hnae3_handle* ae_handle; } ;
struct TYPE_6__ {int num_tqps; } ;
struct hnae3_handle {TYPE_3__ kinfo; } ;
struct ethtool_ringparam {int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_pending; void* rx_max_pending; void* tx_max_pending; } ;
struct TYPE_5__ {TYPE_1__* ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc_num; } ;

/* Variables and functions */
 void* HNS3_RING_MAX_PENDING ; 
 scalar_t__ hns3_nic_resetting (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hns3_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *param)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	int queue_num = h->kinfo.num_tqps;

	if (hns3_nic_resetting(netdev)) {
		netdev_err(netdev, "dev resetting!");
		return;
	}

	param->tx_max_pending = HNS3_RING_MAX_PENDING;
	param->rx_max_pending = HNS3_RING_MAX_PENDING;

	param->tx_pending = priv->ring_data[0].ring->desc_num;
	param->rx_pending = priv->ring_data[queue_num].ring->desc_num;
}