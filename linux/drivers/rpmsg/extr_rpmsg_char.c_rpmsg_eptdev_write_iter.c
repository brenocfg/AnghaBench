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
struct rpmsg_eptdev {int /*<<< orphan*/  ept_lock; int /*<<< orphan*/  ept; } ;
struct kiocb {struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int f_flags; struct rpmsg_eptdev* private_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int EPIPE ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  copy_from_iter_full (void*,size_t,struct iov_iter*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpmsg_send (int /*<<< orphan*/ ,void*,size_t) ; 
 int rpmsg_trysend (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t rpmsg_eptdev_write_iter(struct kiocb *iocb,
				       struct iov_iter *from)
{
	struct file *filp = iocb->ki_filp;
	struct rpmsg_eptdev *eptdev = filp->private_data;
	size_t len = iov_iter_count(from);
	void *kbuf;
	int ret;

	kbuf = kzalloc(len, GFP_KERNEL);
	if (!kbuf)
		return -ENOMEM;

	if (!copy_from_iter_full(kbuf, len, from))
		return -EFAULT;

	if (mutex_lock_interruptible(&eptdev->ept_lock)) {
		ret = -ERESTARTSYS;
		goto free_kbuf;
	}

	if (!eptdev->ept) {
		ret = -EPIPE;
		goto unlock_eptdev;
	}

	if (filp->f_flags & O_NONBLOCK)
		ret = rpmsg_trysend(eptdev->ept, kbuf, len);
	else
		ret = rpmsg_send(eptdev->ept, kbuf, len);

unlock_eptdev:
	mutex_unlock(&eptdev->ept_lock);

free_kbuf:
	kfree(kbuf);
	return ret < 0 ? ret : len;
}