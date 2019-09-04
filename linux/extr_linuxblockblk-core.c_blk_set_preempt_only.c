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
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_PREEMPT_ONLY ; 
 int blk_queue_flag_test_and_set (int /*<<< orphan*/ ,struct request_queue*) ; 

int blk_set_preempt_only(struct request_queue *q)
{
	return blk_queue_flag_test_and_set(QUEUE_FLAG_PREEMPT_ONLY, q);
}