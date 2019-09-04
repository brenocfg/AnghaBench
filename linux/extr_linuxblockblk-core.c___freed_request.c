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
struct request_queue {scalar_t__ nr_requests; } ;
struct request_list {scalar_t__* count; int /*<<< orphan*/ * wait; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_clear_congested (struct request_list*,int) ; 
 int /*<<< orphan*/  blk_clear_rl_full (struct request_list*,int) ; 
 scalar_t__ queue_congestion_off_threshold (struct request_queue*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __freed_request(struct request_list *rl, int sync)
{
	struct request_queue *q = rl->q;

	if (rl->count[sync] < queue_congestion_off_threshold(q))
		blk_clear_congested(rl, sync);

	if (rl->count[sync] + 1 <= q->nr_requests) {
		if (waitqueue_active(&rl->wait[sync]))
			wake_up(&rl->wait[sync]);

		blk_clear_rl_full(rl, sync);
	}
}