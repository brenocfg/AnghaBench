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
struct v4l2_fh {int /*<<< orphan*/  prio; TYPE_1__* vdev; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  fh_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void v4l2_fh_del(struct v4l2_fh *fh)
{
	unsigned long flags;

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	list_del_init(&fh->list);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
	v4l2_prio_close(fh->vdev->prio, fh->prio);
}