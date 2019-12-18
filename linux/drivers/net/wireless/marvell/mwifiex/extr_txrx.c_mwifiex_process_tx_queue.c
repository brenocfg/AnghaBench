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
struct mwifiex_adapter {scalar_t__ tx_lock_flag; scalar_t__ data_sent; int /*<<< orphan*/  tx_data_q; } ;

/* Variables and functions */
 scalar_t__ mwifiex_dequeue_tx_queue (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

void
mwifiex_process_tx_queue(struct mwifiex_adapter *adapter)
{
	do {
		if (adapter->data_sent || adapter->tx_lock_flag)
			break;
		if (mwifiex_dequeue_tx_queue(adapter))
			break;
	} while (!skb_queue_empty(&adapter->tx_data_q));
}