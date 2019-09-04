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
struct vmw_marker_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  lag_time; scalar_t__ lag; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_raw_ns () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void vmw_marker_queue_init(struct vmw_marker_queue *queue)
{
	INIT_LIST_HEAD(&queue->head);
	queue->lag = 0;
	queue->lag_time = ktime_get_raw_ns();
	spin_lock_init(&queue->lock);
}