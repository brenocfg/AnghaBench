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
struct file {struct event_device_data* private_data; } ;
struct event_device_data {int /*<<< orphan*/  events; int /*<<< orphan*/  exist; int /*<<< orphan*/  wq; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  event_queue_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t event_poll(struct file *filp, poll_table *wait)
{
	struct event_device_data *dev_data = filp->private_data;
	__poll_t mask = 0;

	poll_wait(filp, &dev_data->wq, wait);
	if (!dev_data->exist)
		return EPOLLHUP;
	if (!event_queue_empty(dev_data->events))
		mask |= EPOLLIN | EPOLLRDNORM | EPOLLPRI;
	return mask;
}