#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct net_device {int dummy; } ;
struct hns_nic_priv {TYPE_2__* ae_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  desc_num; } ;
struct TYPE_7__ {int /*<<< orphan*/  desc_num; } ;
struct hnae_queue {TYPE_4__ tx_ring; TYPE_3__ rx_ring; } ;
struct hnae_ae_ops {int /*<<< orphan*/  (* get_ring_bdnum_limit ) (struct hnae_queue*,void**) ;} ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; void* tx_max_pending; void* rx_max_pending; } ;
struct TYPE_6__ {TYPE_1__* dev; struct hnae_queue** qs; } ;
struct TYPE_5__ {struct hnae_ae_ops* ops; } ;

/* Variables and functions */
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae_queue*,void**) ; 

__attribute__((used)) static void hns_get_ringparam(struct net_device *net_dev,
			      struct ethtool_ringparam *param)
{
	struct hns_nic_priv *priv = netdev_priv(net_dev);
	struct hnae_ae_ops *ops;
	struct hnae_queue *queue;
	u32 uplimit = 0;

	queue = priv->ae_handle->qs[0];
	ops = priv->ae_handle->dev->ops;

	if (ops->get_ring_bdnum_limit)
		ops->get_ring_bdnum_limit(queue, &uplimit);

	param->rx_max_pending = uplimit;
	param->tx_max_pending = uplimit;
	param->rx_pending = queue->rx_ring.desc_num;
	param->tx_pending = queue->tx_ring.desc_num;
}