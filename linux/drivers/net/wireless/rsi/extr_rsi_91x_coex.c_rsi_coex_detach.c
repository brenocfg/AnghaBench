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
struct rsi_common {scalar_t__ coex_cb; } ;
struct rsi_coex_ctrl_block {int /*<<< orphan*/ * coex_tx_qs; int /*<<< orphan*/  coex_tx_thread; } ;

/* Variables and functions */
 int NUM_COEX_TX_QUEUES ; 
 int /*<<< orphan*/  kfree (struct rsi_coex_ctrl_block*) ; 
 int /*<<< orphan*/  rsi_kill_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void rsi_coex_detach(struct rsi_common *common)
{
	struct rsi_coex_ctrl_block *coex_cb =
		(struct rsi_coex_ctrl_block *)common->coex_cb;
	int cnt;

	rsi_kill_thread(&coex_cb->coex_tx_thread);

	for (cnt = 0; cnt < NUM_COEX_TX_QUEUES; cnt++)
		skb_queue_purge(&coex_cb->coex_tx_qs[cnt]);

	kfree(coex_cb);
}