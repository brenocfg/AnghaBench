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
struct v4l2_fh {TYPE_1__* vdev; int /*<<< orphan*/  list; int /*<<< orphan*/  prio; } ;
struct TYPE_2__ {int /*<<< orphan*/  fh_lock; int /*<<< orphan*/  fh_list; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_prio_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void v4l2_fh_add(struct v4l2_fh *fh)
{
	unsigned long flags;

	v4l2_prio_open(fh->vdev->prio, &fh->prio);
	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	list_add(&fh->list, &fh->vdev->fh_list);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
}