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
struct file {struct evdev_client* private_data; } ;
struct evdev_client {scalar_t__ packet_head; scalar_t__ tail; int /*<<< orphan*/  revoked; struct evdev* evdev; } ;
struct evdev {scalar_t__ exist; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t evdev_poll(struct file *file, poll_table *wait)
{
	struct evdev_client *client = file->private_data;
	struct evdev *evdev = client->evdev;
	__poll_t mask;

	poll_wait(file, &evdev->wait, wait);

	if (evdev->exist && !client->revoked)
		mask = EPOLLOUT | EPOLLWRNORM;
	else
		mask = EPOLLHUP | EPOLLERR;

	if (client->packet_head != client->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}