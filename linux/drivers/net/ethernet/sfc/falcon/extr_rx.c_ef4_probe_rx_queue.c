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
struct ef4_rx_queue {unsigned int ptr_mask; int /*<<< orphan*/ * buffer; struct ef4_nic* efx; } ;
struct ef4_nic {int /*<<< orphan*/  rxq_entries; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int) ; 
 unsigned int EF4_MAX_DMAQ_SIZE ; 
 int /*<<< orphan*/  EF4_MIN_DMAQ_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ef4_nic_probe_rx (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_rx_queue_index (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  roundup_pow_of_two (int /*<<< orphan*/ ) ; 

int ef4_probe_rx_queue(struct ef4_rx_queue *rx_queue)
{
	struct ef4_nic *efx = rx_queue->efx;
	unsigned int entries;
	int rc;

	/* Create the smallest power-of-two aligned ring */
	entries = max(roundup_pow_of_two(efx->rxq_entries), EF4_MIN_DMAQ_SIZE);
	EF4_BUG_ON_PARANOID(entries > EF4_MAX_DMAQ_SIZE);
	rx_queue->ptr_mask = entries - 1;

	netif_dbg(efx, probe, efx->net_dev,
		  "creating RX queue %d size %#x mask %#x\n",
		  ef4_rx_queue_index(rx_queue), efx->rxq_entries,
		  rx_queue->ptr_mask);

	/* Allocate RX buffers */
	rx_queue->buffer = kcalloc(entries, sizeof(*rx_queue->buffer),
				   GFP_KERNEL);
	if (!rx_queue->buffer)
		return -ENOMEM;

	rc = ef4_nic_probe_rx(rx_queue);
	if (rc) {
		kfree(rx_queue->buffer);
		rx_queue->buffer = NULL;
	}

	return rc;
}