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
struct cardstate {int flags; int waiting; int /*<<< orphan*/  mutex; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  at_state; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  EV_SHUTDOWN ; 
 int VALID_MINOR ; 
 int /*<<< orphan*/  cleanup_cs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (struct cardstate*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int gigaset_shutdown(struct cardstate *cs)
{
	mutex_lock(&cs->mutex);

	if (!(cs->flags & VALID_MINOR)) {
		mutex_unlock(&cs->mutex);
		return -ENODEV;
	}

	cs->waiting = 1;

	if (!gigaset_add_event(cs, &cs->at_state, EV_SHUTDOWN, NULL, 0, NULL))
		goto exit;
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	cleanup_cs(cs);

exit:
	mutex_unlock(&cs->mutex);
	return 0;
}