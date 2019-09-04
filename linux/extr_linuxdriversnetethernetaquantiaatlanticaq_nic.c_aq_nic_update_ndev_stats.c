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
struct TYPE_4__ {scalar_t__ multicast; int /*<<< orphan*/  tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_packets; int /*<<< orphan*/  rx_errors; scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct aq_stats_s {scalar_t__ mprc; int /*<<< orphan*/  erpt; scalar_t__ bbtc; scalar_t__ mbtc; scalar_t__ ubtc; scalar_t__ bptc; scalar_t__ mptc; scalar_t__ uptc; int /*<<< orphan*/  erpr; scalar_t__ bbrc; scalar_t__ mbrc; scalar_t__ ubrc; scalar_t__ bprc; scalar_t__ uprc; } ;
struct aq_nic_s {int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; struct net_device* ndev; } ;
struct TYPE_3__ {struct aq_stats_s* (* hw_get_hw_stats ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct aq_stats_s* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aq_nic_update_ndev_stats(struct aq_nic_s *self)
{
	struct net_device *ndev = self->ndev;
	struct aq_stats_s *stats = self->aq_hw_ops->hw_get_hw_stats(self->aq_hw);

	ndev->stats.rx_packets = stats->uprc + stats->mprc + stats->bprc;
	ndev->stats.rx_bytes = stats->ubrc + stats->mbrc + stats->bbrc;
	ndev->stats.rx_errors = stats->erpr;
	ndev->stats.tx_packets = stats->uptc + stats->mptc + stats->bptc;
	ndev->stats.tx_bytes = stats->ubtc + stats->mbtc + stats->bbtc;
	ndev->stats.tx_errors = stats->erpt;
	ndev->stats.multicast = stats->mprc;
}