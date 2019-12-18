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
struct file {struct capidev* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  applid; } ;
struct capidev {int /*<<< orphan*/  recvqueue; int /*<<< orphan*/  recvwait; TYPE_1__ ap; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t
capi_poll(struct file *file, poll_table *wait)
{
	struct capidev *cdev = file->private_data;
	__poll_t mask = 0;

	if (!cdev->ap.applid)
		return EPOLLERR;

	poll_wait(file, &(cdev->recvwait), wait);
	mask = EPOLLOUT | EPOLLWRNORM;
	if (!skb_queue_empty_lockless(&cdev->recvqueue))
		mask |= EPOLLIN | EPOLLRDNORM;
	return mask;
}