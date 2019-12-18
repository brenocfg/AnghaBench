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
struct hns_nic_priv {TYPE_1__* ae_handle; } ;
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  q_num; } ;

/* Variables and functions */
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
hns_get_channels(struct net_device *net_dev, struct ethtool_channels *ch)
{
	struct hns_nic_priv *priv = netdev_priv(net_dev);

	ch->max_rx = priv->ae_handle->q_num;
	ch->max_tx = priv->ae_handle->q_num;

	ch->rx_count = priv->ae_handle->q_num;
	ch->tx_count = priv->ae_handle->q_num;
}