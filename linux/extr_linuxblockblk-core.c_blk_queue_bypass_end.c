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
struct request_queue {scalar_t__ bypass_depth; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_BYPASS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void blk_queue_bypass_end(struct request_queue *q)
{
	spin_lock_irq(q->queue_lock);
	if (!--q->bypass_depth)
		queue_flag_clear(QUEUE_FLAG_BYPASS, q);
	WARN_ON_ONCE(q->bypass_depth < 0);
	spin_unlock_irq(q->queue_lock);
}