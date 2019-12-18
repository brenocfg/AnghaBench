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
struct vhost_poll {int /*<<< orphan*/  wait; int /*<<< orphan*/  table; scalar_t__ wqh; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPOLLERR ; 
 int /*<<< orphan*/  poll_to_key (int) ; 
 int vfs_poll (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_poll_stop (struct vhost_poll*) ; 
 int /*<<< orphan*/  vhost_poll_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vhost_poll_start(struct vhost_poll *poll, struct file *file)
{
	__poll_t mask;

	if (poll->wqh)
		return 0;

	mask = vfs_poll(file, &poll->table);
	if (mask)
		vhost_poll_wakeup(&poll->wait, 0, 0, poll_to_key(mask));
	if (mask & EPOLLERR) {
		vhost_poll_stop(poll);
		return -EINVAL;
	}

	return 0;
}