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
struct efx_rx_queue {unsigned int added_count; unsigned int removed_count; unsigned int fast_fill_trigger; unsigned int min_fill; unsigned int max_fill; scalar_t__ notified_count; struct efx_nic* efx; int /*<<< orphan*/  refill_enabled; } ;
struct efx_nic {unsigned int rxq_entries; unsigned int rx_pages_per_batch; unsigned int rx_bufs_per_page; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int efx_init_rx_buffers (struct efx_rx_queue*,int) ; 
 int /*<<< orphan*/  efx_nic_notify_rx_desc (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_rx_queue_index (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_schedule_slow_fill (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  netif_vdbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  rx_status ; 
 scalar_t__ unlikely (int) ; 

void efx_fast_push_rx_descriptors(struct efx_rx_queue *rx_queue, bool atomic)
{
	struct efx_nic *efx = rx_queue->efx;
	unsigned int fill_level, batch_size;
	int space, rc = 0;

	if (!rx_queue->refill_enabled)
		return;

	/* Calculate current fill level, and exit if we don't need to fill */
	fill_level = (rx_queue->added_count - rx_queue->removed_count);
	EFX_WARN_ON_ONCE_PARANOID(fill_level > rx_queue->efx->rxq_entries);
	if (fill_level >= rx_queue->fast_fill_trigger)
		goto out;

	/* Record minimum fill level */
	if (unlikely(fill_level < rx_queue->min_fill)) {
		if (fill_level)
			rx_queue->min_fill = fill_level;
	}

	batch_size = efx->rx_pages_per_batch * efx->rx_bufs_per_page;
	space = rx_queue->max_fill - fill_level;
	EFX_WARN_ON_ONCE_PARANOID(space < batch_size);

	netif_vdbg(rx_queue->efx, rx_status, rx_queue->efx->net_dev,
		   "RX queue %d fast-filling descriptor ring from"
		   " level %d to level %d\n",
		   efx_rx_queue_index(rx_queue), fill_level,
		   rx_queue->max_fill);


	do {
		rc = efx_init_rx_buffers(rx_queue, atomic);
		if (unlikely(rc)) {
			/* Ensure that we don't leave the rx queue empty */
			efx_schedule_slow_fill(rx_queue);
			goto out;
		}
	} while ((space -= batch_size) >= batch_size);

	netif_vdbg(rx_queue->efx, rx_status, rx_queue->efx->net_dev,
		   "RX queue %d fast-filled descriptor ring "
		   "to level %d\n", efx_rx_queue_index(rx_queue),
		   rx_queue->added_count - rx_queue->removed_count);

 out:
	if (rx_queue->notified_count != rx_queue->added_count)
		efx_nic_notify_rx_desc(rx_queue);
}