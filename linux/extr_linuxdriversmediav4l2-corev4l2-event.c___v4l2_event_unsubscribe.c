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
struct v4l2_subscribed_event {unsigned int in_use; int /*<<< orphan*/  list; TYPE_1__* events; struct v4l2_fh* fh; } ;
struct v4l2_fh {int /*<<< orphan*/  navailable; TYPE_2__* vdev; int /*<<< orphan*/  subscribe_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  fh_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 size_t sev_pos (struct v4l2_subscribed_event*,unsigned int) ; 

__attribute__((used)) static void __v4l2_event_unsubscribe(struct v4l2_subscribed_event *sev)
{
	struct v4l2_fh *fh = sev->fh;
	unsigned int i;

	lockdep_assert_held(&fh->subscribe_lock);
	assert_spin_locked(&fh->vdev->fh_lock);

	/* Remove any pending events for this subscription */
	for (i = 0; i < sev->in_use; i++) {
		list_del(&sev->events[sev_pos(sev, i)].list);
		fh->navailable--;
	}
	list_del(&sev->list);
}