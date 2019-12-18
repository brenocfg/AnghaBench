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
struct poll_table_struct {int dummy; } ;
struct file {struct devx_async_event_file* private_data; } ;
struct devx_async_event_file {int /*<<< orphan*/  lock; int /*<<< orphan*/  event_list; scalar_t__ is_destroyed; int /*<<< orphan*/  poll_wait; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDHUP ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t devx_async_event_poll(struct file *filp,
				      struct poll_table_struct *wait)
{
	struct devx_async_event_file *ev_file = filp->private_data;
	__poll_t pollflags = 0;

	poll_wait(filp, &ev_file->poll_wait, wait);

	spin_lock_irq(&ev_file->lock);
	if (ev_file->is_destroyed)
		pollflags = EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;
	else if (!list_empty(&ev_file->event_list))
		pollflags = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irq(&ev_file->lock);

	return pollflags;
}