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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  xmit_finished; int /*<<< orphan*/  xmit_called; int /*<<< orphan*/  xmit_off; int /*<<< orphan*/  xmit_on; } ;
struct qlcnic_host_tx_ring {TYPE_1__ tx_stats; } ;

/* Variables and functions */
 void* QLCNIC_FILL_STATS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *qlcnic_fill_tx_queue_stats(u64 *data, void *stats)
{
	struct qlcnic_host_tx_ring *tx_ring;

	tx_ring = (struct qlcnic_host_tx_ring *)stats;

	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_on);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_off);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_called);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_finished);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.tx_bytes);

	return data;
}