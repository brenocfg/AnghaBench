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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;struct dma_chan* chan; int /*<<< orphan*/  callback_param; int /*<<< orphan*/  callback; } ;
struct async_submit_ctl {int flags; int /*<<< orphan*/  cb_param; int /*<<< orphan*/  cb_fn; struct dma_async_tx_descriptor* depend_tx; } ;
typedef  enum submit_disposition { ____Placeholder_submit_disposition } submit_disposition ;

/* Variables and functions */
 int ASYNC_TX_ACK ; 
#define  ASYNC_TX_CHANNEL_SWITCH 130 
#define  ASYNC_TX_DIRECT_SUBMIT 129 
#define  ASYNC_TX_SUBMITTED 128 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  async_tx_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  async_tx_channel_switch (struct dma_async_tx_descriptor*,struct dma_async_tx_descriptor*) ; 
 scalar_t__ async_tx_test_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub1 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub2 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_chain (struct dma_async_tx_descriptor*,struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_clear_parent (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_lock (struct dma_async_tx_descriptor*) ; 
 scalar_t__ txd_next (struct dma_async_tx_descriptor*) ; 
 scalar_t__ txd_parent (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txd_unlock (struct dma_async_tx_descriptor*) ; 

void
async_tx_submit(struct dma_chan *chan, struct dma_async_tx_descriptor *tx,
		struct async_submit_ctl *submit)
{
	struct dma_async_tx_descriptor *depend_tx = submit->depend_tx;

	tx->callback = submit->cb_fn;
	tx->callback_param = submit->cb_param;

	if (depend_tx) {
		enum submit_disposition s;

		/* sanity check the dependency chain:
		 * 1/ if ack is already set then we cannot be sure
		 * we are referring to the correct operation
		 * 2/ dependencies are 1:1 i.e. two transactions can
		 * not depend on the same parent
		 */
		BUG_ON(async_tx_test_ack(depend_tx) || txd_next(depend_tx) ||
		       txd_parent(tx));

		/* the lock prevents async_tx_run_dependencies from missing
		 * the setting of ->next when ->parent != NULL
		 */
		txd_lock(depend_tx);
		if (txd_parent(depend_tx)) {
			/* we have a parent so we can not submit directly
			 * if we are staying on the same channel: append
			 * else: channel switch
			 */
			if (depend_tx->chan == chan) {
				txd_chain(depend_tx, tx);
				s = ASYNC_TX_SUBMITTED;
			} else
				s = ASYNC_TX_CHANNEL_SWITCH;
		} else {
			/* we do not have a parent so we may be able to submit
			 * directly if we are staying on the same channel
			 */
			if (depend_tx->chan == chan)
				s = ASYNC_TX_DIRECT_SUBMIT;
			else
				s = ASYNC_TX_CHANNEL_SWITCH;
		}
		txd_unlock(depend_tx);

		switch (s) {
		case ASYNC_TX_SUBMITTED:
			break;
		case ASYNC_TX_CHANNEL_SWITCH:
			async_tx_channel_switch(depend_tx, tx);
			break;
		case ASYNC_TX_DIRECT_SUBMIT:
			txd_clear_parent(tx);
			tx->tx_submit(tx);
			break;
		}
	} else {
		txd_clear_parent(tx);
		tx->tx_submit(tx);
	}

	if (submit->flags & ASYNC_TX_ACK)
		async_tx_ack(tx);

	if (depend_tx)
		async_tx_ack(depend_tx);
}