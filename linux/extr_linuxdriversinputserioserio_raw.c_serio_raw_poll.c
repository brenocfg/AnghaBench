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
struct serio_raw_client {struct serio_raw* serio_raw; } ;
struct serio_raw {scalar_t__ head; scalar_t__ tail; scalar_t__ dead; int /*<<< orphan*/  wait; } ;
struct file {struct serio_raw_client* private_data; } ;
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

__attribute__((used)) static __poll_t serio_raw_poll(struct file *file, poll_table *wait)
{
	struct serio_raw_client *client = file->private_data;
	struct serio_raw *serio_raw = client->serio_raw;
	__poll_t mask;

	poll_wait(file, &serio_raw->wait, wait);

	mask = serio_raw->dead ? EPOLLHUP | EPOLLERR : EPOLLOUT | EPOLLWRNORM;
	if (serio_raw->head != serio_raw->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}