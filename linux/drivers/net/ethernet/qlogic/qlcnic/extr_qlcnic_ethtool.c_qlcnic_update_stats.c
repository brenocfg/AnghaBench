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
typedef  int /*<<< orphan*/  tx_stats ;
struct qlcnic_tx_queue_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  xmit_finished; int /*<<< orphan*/  xmit_called; int /*<<< orphan*/  xmit_off; int /*<<< orphan*/  xmit_on; } ;
struct TYPE_3__ {scalar_t__ tx_bytes; scalar_t__ xmit_finished; scalar_t__ xmit_called; scalar_t__ xmit_off; scalar_t__ xmit_on; } ;
struct qlcnic_host_tx_ring {TYPE_1__ tx_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  txbytes; int /*<<< orphan*/  xmitfinished; int /*<<< orphan*/  xmitcalled; int /*<<< orphan*/  xmit_off; int /*<<< orphan*/  xmit_on; } ;
struct qlcnic_adapter {int drv_tx_rings; TYPE_2__ stats; struct qlcnic_host_tx_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct qlcnic_tx_queue_stats*,int /*<<< orphan*/ ,int) ; 

void qlcnic_update_stats(struct qlcnic_adapter *adapter)
{
	struct qlcnic_tx_queue_stats tx_stats;
	struct qlcnic_host_tx_ring *tx_ring;
	int ring;

	memset(&tx_stats, 0, sizeof(tx_stats));
	for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
		tx_ring = &adapter->tx_ring[ring];
		tx_stats.xmit_on += tx_ring->tx_stats.xmit_on;
		tx_stats.xmit_off += tx_ring->tx_stats.xmit_off;
		tx_stats.xmit_called += tx_ring->tx_stats.xmit_called;
		tx_stats.xmit_finished += tx_ring->tx_stats.xmit_finished;
		tx_stats.tx_bytes += tx_ring->tx_stats.tx_bytes;
	}

	adapter->stats.xmit_on = tx_stats.xmit_on;
	adapter->stats.xmit_off = tx_stats.xmit_off;
	adapter->stats.xmitcalled = tx_stats.xmit_called;
	adapter->stats.xmitfinished = tx_stats.xmit_finished;
	adapter->stats.txbytes = tx_stats.tx_bytes;
}