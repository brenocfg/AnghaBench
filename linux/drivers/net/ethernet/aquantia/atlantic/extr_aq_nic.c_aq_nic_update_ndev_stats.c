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
struct TYPE_4__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct aq_stats_s {int /*<<< orphan*/  mprc; int /*<<< orphan*/  erpt; int /*<<< orphan*/  dma_oct_tc; int /*<<< orphan*/  dma_pkt_tc; int /*<<< orphan*/  dpc; int /*<<< orphan*/  erpr; int /*<<< orphan*/  dma_oct_rc; int /*<<< orphan*/  dma_pkt_rc; } ;
struct aq_nic_s {int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; struct net_device* ndev; } ;
struct TYPE_3__ {struct aq_stats_s* (* hw_get_hw_stats ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct aq_stats_s* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aq_nic_update_ndev_stats(struct aq_nic_s *self)
{
	struct net_device *ndev = self->ndev;
	struct aq_stats_s *stats = self->aq_hw_ops->hw_get_hw_stats(self->aq_hw);

	ndev->stats.rx_packets = stats->dma_pkt_rc;
	ndev->stats.rx_bytes = stats->dma_oct_rc;
	ndev->stats.rx_errors = stats->erpr;
	ndev->stats.rx_dropped = stats->dpc;
	ndev->stats.tx_packets = stats->dma_pkt_tc;
	ndev->stats.tx_bytes = stats->dma_oct_tc;
	ndev->stats.tx_errors = stats->erpt;
	ndev->stats.multicast = stats->mprc;
}