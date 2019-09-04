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
struct sge_eth_txq {scalar_t__ vlan_ins; scalar_t__ tx_cso; scalar_t__ tso; } ;
struct TYPE_4__ {scalar_t__ lro_merged; scalar_t__ lro_pkts; scalar_t__ vlan_ex; scalar_t__ rx_cso; } ;
struct sge_eth_rxq {TYPE_2__ stats; } ;
struct queue_port_stats {int /*<<< orphan*/  lro_merged; int /*<<< orphan*/  lro_pkts; int /*<<< orphan*/  vlan_ins; int /*<<< orphan*/  vlan_ex; int /*<<< orphan*/  rx_csum; int /*<<< orphan*/  tx_csum; int /*<<< orphan*/  tso; } ;
struct port_info {size_t first_qset; int nqsets; } ;
struct TYPE_3__ {struct sge_eth_rxq* ethrxq; struct sge_eth_txq* ethtxq; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct queue_port_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void collect_sge_port_stats(const struct adapter *adapter,
				   const struct port_info *pi,
				   struct queue_port_stats *stats)
{
	const struct sge_eth_txq *txq = &adapter->sge.ethtxq[pi->first_qset];
	const struct sge_eth_rxq *rxq = &adapter->sge.ethrxq[pi->first_qset];
	int qs;

	memset(stats, 0, sizeof(*stats));
	for (qs = 0; qs < pi->nqsets; qs++, rxq++, txq++) {
		stats->tso += txq->tso;
		stats->tx_csum += txq->tx_cso;
		stats->rx_csum += rxq->stats.rx_cso;
		stats->vlan_ex += rxq->stats.vlan_ex;
		stats->vlan_ins += txq->vlan_ins;
		stats->lro_pkts += rxq->stats.lro_pkts;
		stats->lro_merged += rxq->stats.lro_merged;
	}
}