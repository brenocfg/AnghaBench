#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efx_tx_queue {int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * cb_page; TYPE_1__* efx; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_nic_free_buffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_nic_remove_tx (struct efx_tx_queue*) ; 
 int efx_tx_cb_page_count (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void efx_remove_tx_queue(struct efx_tx_queue *tx_queue)
{
	int i;

	if (!tx_queue->buffer)
		return;

	netif_dbg(tx_queue->efx, drv, tx_queue->efx->net_dev,
		  "destroying TX queue %d\n", tx_queue->queue);
	efx_nic_remove_tx(tx_queue);

	if (tx_queue->cb_page) {
		for (i = 0; i < efx_tx_cb_page_count(tx_queue); i++)
			efx_nic_free_buffer(tx_queue->efx,
					    &tx_queue->cb_page[i]);
		kfree(tx_queue->cb_page);
		tx_queue->cb_page = NULL;
	}

	kfree(tx_queue->buffer);
	tx_queue->buffer = NULL;
}