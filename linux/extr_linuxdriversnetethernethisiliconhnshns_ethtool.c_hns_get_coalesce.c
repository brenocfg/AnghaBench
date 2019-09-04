#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns_nic_priv {TYPE_2__* ae_handle; } ;
struct hnae_ae_ops {int /*<<< orphan*/  (* get_coalesce_range ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_max_coalesced_frames ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_coalesce_usecs ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  tx_coalesce_usecs_high; int /*<<< orphan*/  rx_coalesce_usecs_low; int /*<<< orphan*/  tx_coalesce_usecs_low; int /*<<< orphan*/  rx_max_coalesced_frames_high; int /*<<< orphan*/  tx_max_coalesced_frames_high; int /*<<< orphan*/  rx_max_coalesced_frames_low; int /*<<< orphan*/  tx_max_coalesced_frames_low; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  use_adaptive_tx_coalesce; int /*<<< orphan*/  use_adaptive_rx_coalesce; } ;
struct TYPE_6__ {int /*<<< orphan*/  coal_adapt_en; TYPE_1__* dev; } ;
struct TYPE_5__ {struct hnae_ae_ops* ops; } ;

/* Variables and functions */
 int ESRCH ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_get_coalesce(struct net_device *net_dev,
			    struct ethtool_coalesce *ec)
{
	struct hns_nic_priv *priv = netdev_priv(net_dev);
	struct hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;

	ec->use_adaptive_rx_coalesce = priv->ae_handle->coal_adapt_en;
	ec->use_adaptive_tx_coalesce = priv->ae_handle->coal_adapt_en;

	if ((!ops->get_coalesce_usecs) ||
	    (!ops->get_max_coalesced_frames))
		return -ESRCH;

	ops->get_coalesce_usecs(priv->ae_handle,
					&ec->tx_coalesce_usecs,
					&ec->rx_coalesce_usecs);

	ops->get_max_coalesced_frames(
		priv->ae_handle,
		&ec->tx_max_coalesced_frames,
		&ec->rx_max_coalesced_frames);

	ops->get_coalesce_range(priv->ae_handle,
				&ec->tx_max_coalesced_frames_low,
				&ec->rx_max_coalesced_frames_low,
				&ec->tx_max_coalesced_frames_high,
				&ec->rx_max_coalesced_frames_high,
				&ec->tx_coalesce_usecs_low,
				&ec->rx_coalesce_usecs_low,
				&ec->tx_coalesce_usecs_high,
				&ec->rx_coalesce_usecs_high);

	return 0;
}