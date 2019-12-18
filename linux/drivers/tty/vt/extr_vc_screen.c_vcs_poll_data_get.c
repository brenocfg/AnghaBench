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
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct vcs_poll_data {TYPE_1__ notifier; int /*<<< orphan*/  event; int /*<<< orphan*/  waitq; int /*<<< orphan*/  cons_num; } ;
struct file {int /*<<< orphan*/  f_lock; struct vcs_poll_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VT_UPDATE ; 
 int /*<<< orphan*/  console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vcs_poll_data*) ; 
 struct vcs_poll_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ register_vt_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcs_notifier ; 
 int /*<<< orphan*/  vcs_poll_data_free (struct vcs_poll_data*) ; 

__attribute__((used)) static struct vcs_poll_data *
vcs_poll_data_get(struct file *file)
{
	struct vcs_poll_data *poll = file->private_data, *kill = NULL;

	if (poll)
		return poll;

	poll = kzalloc(sizeof(*poll), GFP_KERNEL);
	if (!poll)
		return NULL;
	poll->cons_num = console(file_inode(file));
	init_waitqueue_head(&poll->waitq);
	poll->notifier.notifier_call = vcs_notifier;
	/*
	 * In order not to lose any update event, we must pretend one might
	 * have occurred before we have a chance to register our notifier.
	 * This is also how user space has come to detect which kernels
	 * support POLLPRI on /dev/vcs* devices i.e. using poll() with
	 * POLLPRI and a zero timeout.
	 */
	poll->event = VT_UPDATE;

	if (register_vt_notifier(&poll->notifier) != 0) {
		kfree(poll);
		return NULL;
	}

	/*
	 * This code may be called either through ->poll() or ->fasync().
	 * If we have two threads using the same file descriptor, they could
	 * both enter this function, both notice that the structure hasn't
	 * been allocated yet and go ahead allocating it in parallel, but
	 * only one of them must survive and be shared otherwise we'd leak
	 * memory with a dangling notifier callback.
	 */
	spin_lock(&file->f_lock);
	if (!file->private_data) {
		file->private_data = poll;
	} else {
		/* someone else raced ahead of us */
		kill = poll;
		poll = file->private_data;
	}
	spin_unlock(&file->f_lock);
	if (kill)
		vcs_poll_data_free(kill);

	return poll;
}