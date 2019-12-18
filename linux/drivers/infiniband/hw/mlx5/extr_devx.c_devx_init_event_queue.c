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
struct devx_async_event_queue {scalar_t__ is_destroyed; int /*<<< orphan*/  bytes_in_use; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  event_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void devx_init_event_queue(struct devx_async_event_queue *ev_queue)
{
	spin_lock_init(&ev_queue->lock);
	INIT_LIST_HEAD(&ev_queue->event_list);
	init_waitqueue_head(&ev_queue->poll_wait);
	atomic_set(&ev_queue->bytes_in_use, 0);
	ev_queue->is_destroyed = 0;
}