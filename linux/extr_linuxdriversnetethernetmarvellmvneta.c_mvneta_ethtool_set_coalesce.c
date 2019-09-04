#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct mvneta_tx_queue {int /*<<< orphan*/  done_pkts_coal; } ;
struct mvneta_rx_queue {int /*<<< orphan*/  time_coal; int /*<<< orphan*/  pkts_coal; } ;
struct mvneta_port {struct mvneta_tx_queue* txqs; struct mvneta_rx_queue* rxqs; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_rx_pkts_coal_set (struct mvneta_port*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_rx_time_coal_set (struct mvneta_port*,struct mvneta_rx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_tx_done_pkts_coal_set (struct mvneta_port*,struct mvneta_tx_queue*,int /*<<< orphan*/ ) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int rxq_number ; 
 int txq_number ; 

__attribute__((used)) static int mvneta_ethtool_set_coalesce(struct net_device *dev,
				       struct ethtool_coalesce *c)
{
	struct mvneta_port *pp = netdev_priv(dev);
	int queue;

	for (queue = 0; queue < rxq_number; queue++) {
		struct mvneta_rx_queue *rxq = &pp->rxqs[queue];
		rxq->time_coal = c->rx_coalesce_usecs;
		rxq->pkts_coal = c->rx_max_coalesced_frames;
		mvneta_rx_pkts_coal_set(pp, rxq, rxq->pkts_coal);
		mvneta_rx_time_coal_set(pp, rxq, rxq->time_coal);
	}

	for (queue = 0; queue < txq_number; queue++) {
		struct mvneta_tx_queue *txq = &pp->txqs[queue];
		txq->done_pkts_coal = c->tx_max_coalesced_frames;
		mvneta_tx_done_pkts_coal_set(pp, txq, txq->done_pkts_coal);
	}

	return 0;
}