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
typedef  scalar_t__ u64 ;
struct vmw_marker_queue {scalar_t__ lag; int /*<<< orphan*/  lock; scalar_t__ lag_time; } ;

/* Variables and functions */
 scalar_t__ ktime_get_raw_ns () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 vmw_fifo_lag(struct vmw_marker_queue *queue)
{
	u64 now;

	spin_lock(&queue->lock);
	now = ktime_get_raw_ns();
	queue->lag += now - queue->lag_time;
	queue->lag_time = now;
	spin_unlock(&queue->lock);
	return queue->lag;
}