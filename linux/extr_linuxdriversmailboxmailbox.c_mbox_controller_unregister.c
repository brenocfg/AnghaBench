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
struct mbox_controller {int num_chans; int /*<<< orphan*/  poll_hrt; scalar_t__ txdone_poll; int /*<<< orphan*/ * chans; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  con_mutex ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mbox_controller_unregister(struct mbox_controller *mbox)
{
	int i;

	if (!mbox)
		return;

	mutex_lock(&con_mutex);

	list_del(&mbox->node);

	for (i = 0; i < mbox->num_chans; i++)
		mbox_free_channel(&mbox->chans[i]);

	if (mbox->txdone_poll)
		hrtimer_cancel(&mbox->poll_hrt);

	mutex_unlock(&con_mutex);
}