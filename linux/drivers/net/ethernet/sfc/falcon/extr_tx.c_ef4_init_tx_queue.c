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
struct ef4_tx_queue {int empty_read_count; int xmit_more_available; int tx_min_size; int initialised; scalar_t__ old_read_count; scalar_t__ read_count; scalar_t__ old_write_count; scalar_t__ write_count; scalar_t__ insert_count; int /*<<< orphan*/  queue; struct ef4_nic* efx; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EF4_EMPTY_COUNT_VALID ; 
 scalar_t__ EF4_WORKAROUND_15592 (struct ef4_nic*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_nic_init_tx (struct ef4_tx_queue*) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void ef4_init_tx_queue(struct ef4_tx_queue *tx_queue)
{
	struct ef4_nic *efx = tx_queue->efx;

	netif_dbg(efx, drv, efx->net_dev,
		  "initialising TX queue %d\n", tx_queue->queue);

	tx_queue->insert_count = 0;
	tx_queue->write_count = 0;
	tx_queue->old_write_count = 0;
	tx_queue->read_count = 0;
	tx_queue->old_read_count = 0;
	tx_queue->empty_read_count = 0 | EF4_EMPTY_COUNT_VALID;
	tx_queue->xmit_more_available = false;

	/* Some older hardware requires Tx writes larger than 32. */
	tx_queue->tx_min_size = EF4_WORKAROUND_15592(efx) ? 33 : 0;

	/* Set up TX descriptor ring */
	ef4_nic_init_tx(tx_queue);

	tx_queue->initialised = true;
}