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
struct aggr_info {struct aggr_info* aggr_conn; int /*<<< orphan*/  rx_amsdu_freeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  aggr_reset_state (struct aggr_info*) ; 
 int /*<<< orphan*/  kfree (struct aggr_info*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void aggr_module_destroy(struct aggr_info *aggr_info)
{
	if (!aggr_info)
		return;

	aggr_reset_state(aggr_info->aggr_conn);
	skb_queue_purge(&aggr_info->rx_amsdu_freeq);
	kfree(aggr_info->aggr_conn);
	kfree(aggr_info);
}