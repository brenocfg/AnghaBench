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
struct request_queue {int /*<<< orphan*/  mq_freeze_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_PREEMPT_ONLY ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void blk_clear_preempt_only(struct request_queue *q)
{
	blk_queue_flag_clear(QUEUE_FLAG_PREEMPT_ONLY, q);
	wake_up_all(&q->mq_freeze_wq);
}