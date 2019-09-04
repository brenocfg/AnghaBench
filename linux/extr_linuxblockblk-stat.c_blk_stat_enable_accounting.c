#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* stats; } ;
struct TYPE_2__ {int enable_accounting; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_STATS ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void blk_stat_enable_accounting(struct request_queue *q)
{
	spin_lock(&q->stats->lock);
	q->stats->enable_accounting = true;
	blk_queue_flag_set(QUEUE_FLAG_STATS, q);
	spin_unlock(&q->stats->lock);
}