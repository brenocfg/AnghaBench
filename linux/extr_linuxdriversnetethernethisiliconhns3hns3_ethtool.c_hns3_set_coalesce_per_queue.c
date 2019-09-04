#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct hns3_nic_priv {TYPE_2__* ring_data; struct hnae3_handle* ae_handle; } ;
struct TYPE_12__ {int /*<<< orphan*/  int_gl; int /*<<< orphan*/  gl_adapt_enable; } ;
struct TYPE_13__ {TYPE_5__ coal; } ;
struct TYPE_10__ {int /*<<< orphan*/  int_gl; int /*<<< orphan*/  gl_adapt_enable; } ;
struct TYPE_11__ {TYPE_3__ coal; } ;
struct hns3_enet_tqp_vector {TYPE_6__ rx_group; TYPE_4__ tx_group; } ;
struct TYPE_14__ {int num_tqps; int /*<<< orphan*/  int_rl_setting; } ;
struct hnae3_handle {TYPE_7__ kinfo; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  use_adaptive_rx_coalesce; int /*<<< orphan*/  use_adaptive_tx_coalesce; } ;
struct TYPE_9__ {TYPE_1__* ring; } ;
struct TYPE_8__ {struct hns3_enet_tqp_vector* tqp_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_set_vector_coalesce_rl (struct hns3_enet_tqp_vector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_set_vector_coalesce_rx_gl (struct hns3_enet_tqp_vector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_set_vector_coalesce_tx_gl (struct hns3_enet_tqp_vector*,int /*<<< orphan*/ ) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hns3_set_coalesce_per_queue(struct net_device *netdev,
					struct ethtool_coalesce *cmd,
					u32 queue)
{
	struct hns3_enet_tqp_vector *tx_vector, *rx_vector;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	int queue_num = h->kinfo.num_tqps;

	tx_vector = priv->ring_data[queue].ring->tqp_vector;
	rx_vector = priv->ring_data[queue_num + queue].ring->tqp_vector;

	tx_vector->tx_group.coal.gl_adapt_enable =
				cmd->use_adaptive_tx_coalesce;
	rx_vector->rx_group.coal.gl_adapt_enable =
				cmd->use_adaptive_rx_coalesce;

	tx_vector->tx_group.coal.int_gl = cmd->tx_coalesce_usecs;
	rx_vector->rx_group.coal.int_gl = cmd->rx_coalesce_usecs;

	hns3_set_vector_coalesce_tx_gl(tx_vector,
				       tx_vector->tx_group.coal.int_gl);
	hns3_set_vector_coalesce_rx_gl(rx_vector,
				       rx_vector->rx_group.coal.int_gl);

	hns3_set_vector_coalesce_rl(tx_vector, h->kinfo.int_rl_setting);
	hns3_set_vector_coalesce_rl(rx_vector, h->kinfo.int_rl_setting);
}