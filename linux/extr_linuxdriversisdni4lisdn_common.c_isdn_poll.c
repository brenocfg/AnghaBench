#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {TYPE_1__** drv; int /*<<< orphan*/  info_waitq; } ;
struct TYPE_3__ {scalar_t__ stavail; int /*<<< orphan*/  st_waitq; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 unsigned int ISDN_MINOR_CTRL ; 
 unsigned int ISDN_MINOR_CTRLMAX ; 
 unsigned int ISDN_MINOR_STATUS ; 
 TYPE_2__* dev ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 unsigned int iminor (int /*<<< orphan*/ ) ; 
 int isdn_minor2drv (unsigned int) ; 
 int /*<<< orphan*/  isdn_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t
isdn_poll(struct file *file, poll_table *wait)
{
	__poll_t mask = 0;
	unsigned int minor = iminor(file_inode(file));
	int drvidx = isdn_minor2drv(minor - ISDN_MINOR_CTRL);

	mutex_lock(&isdn_mutex);
	if (minor == ISDN_MINOR_STATUS) {
		poll_wait(file, &(dev->info_waitq), wait);
		/* mask = EPOLLOUT | EPOLLWRNORM; */
		if (file->private_data) {
			mask |= EPOLLIN | EPOLLRDNORM;
		}
		goto out;
	}
	if (minor >= ISDN_MINOR_CTRL && minor <= ISDN_MINOR_CTRLMAX) {
		if (drvidx < 0) {
			/* driver deregistered while file open */
			mask = EPOLLHUP;
			goto out;
		}
		poll_wait(file, &(dev->drv[drvidx]->st_waitq), wait);
		mask = EPOLLOUT | EPOLLWRNORM;
		if (dev->drv[drvidx]->stavail) {
			mask |= EPOLLIN | EPOLLRDNORM;
		}
		goto out;
	}
#ifdef CONFIG_ISDN_PPP
	if (minor <= ISDN_MINOR_PPPMAX) {
		mask = isdn_ppp_poll(file, wait);
		goto out;
	}
#endif
	mask = EPOLLERR;
out:
	mutex_unlock(&isdn_mutex);
	return mask;
}