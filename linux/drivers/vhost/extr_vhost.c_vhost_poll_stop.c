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
struct vhost_poll {int /*<<< orphan*/ * wqh; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void vhost_poll_stop(struct vhost_poll *poll)
{
	if (poll->wqh) {
		remove_wait_queue(poll->wqh, &poll->wait);
		poll->wqh = NULL;
	}
}