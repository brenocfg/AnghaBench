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
struct request_queue {int /*<<< orphan*/  q_usage_counter; int /*<<< orphan*/  mq_freeze_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void blk_mq_freeze_queue_wait(struct request_queue *q)
{
	wait_event(q->mq_freeze_wq, percpu_ref_is_zero(&q->q_usage_counter));
}