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
struct virqfd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfio_irqfd_cleanup_wq ; 
 int /*<<< orphan*/  virqfd_deactivate (struct virqfd*) ; 
 int /*<<< orphan*/  virqfd_lock ; 

void vfio_virqfd_disable(struct virqfd **pvirqfd)
{
	unsigned long flags;

	spin_lock_irqsave(&virqfd_lock, flags);

	if (*pvirqfd) {
		virqfd_deactivate(*pvirqfd);
		*pvirqfd = NULL;
	}

	spin_unlock_irqrestore(&virqfd_lock, flags);

	/*
	 * Block until we know all outstanding shutdown jobs have completed.
	 * Even if we don't queue the job, flush the wq to be sure it's
	 * been released.
	 */
	flush_workqueue(vfio_irqfd_cleanup_wq);
}