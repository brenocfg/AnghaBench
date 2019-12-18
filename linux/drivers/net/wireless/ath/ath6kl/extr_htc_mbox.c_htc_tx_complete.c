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
struct list_head {int dummy; } ;
struct htc_endpoint {int /*<<< orphan*/  target; int /*<<< orphan*/  eid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_tx_complete (int /*<<< orphan*/ ,struct list_head*) ; 
 int /*<<< orphan*/  get_queue_depth (struct list_head*) ; 
 scalar_t__ list_empty (struct list_head*) ; 

__attribute__((used)) static void htc_tx_complete(struct htc_endpoint *endpoint,
			    struct list_head *txq)
{
	if (list_empty(txq))
		return;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc tx complete ep %d pkts %d\n",
		   endpoint->eid, get_queue_depth(txq));

	ath6kl_tx_complete(endpoint->target, txq);
}