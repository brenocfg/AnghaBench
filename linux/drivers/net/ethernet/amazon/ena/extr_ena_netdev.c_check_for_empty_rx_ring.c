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
struct TYPE_2__ {int /*<<< orphan*/  empty_rx_ring; } ;
struct ena_ring {int ring_size; scalar_t__ empty_rx_queue; int /*<<< orphan*/  napi; int /*<<< orphan*/  syncp; TYPE_1__ rx_stats; int /*<<< orphan*/  ena_com_io_sq; } ;
struct ena_adapter {int num_queues; int /*<<< orphan*/  netdev; struct ena_ring* rx_ring; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ EMPTY_RX_REFILL ; 
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  drv ; 
 int ena_com_free_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void check_for_empty_rx_ring(struct ena_adapter *adapter)
{
	struct ena_ring *rx_ring;
	int i, refill_required;

	if (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		return;

	if (test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))
		return;

	for (i = 0; i < adapter->num_queues; i++) {
		rx_ring = &adapter->rx_ring[i];

		refill_required =
			ena_com_free_desc(rx_ring->ena_com_io_sq);
		if (unlikely(refill_required == (rx_ring->ring_size - 1))) {
			rx_ring->empty_rx_queue++;

			if (rx_ring->empty_rx_queue >= EMPTY_RX_REFILL) {
				u64_stats_update_begin(&rx_ring->syncp);
				rx_ring->rx_stats.empty_rx_ring++;
				u64_stats_update_end(&rx_ring->syncp);

				netif_err(adapter, drv, adapter->netdev,
					  "trigger refill for ring %d\n", i);

				napi_schedule(rx_ring->napi);
				rx_ring->empty_rx_queue = 0;
			}
		} else {
			rx_ring->empty_rx_queue = 0;
		}
	}
}