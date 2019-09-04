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
struct cardstate {int connected; scalar_t__ mstate; int control_state; int waiting; int /*<<< orphan*/  mutex; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  at_state; TYPE_1__* ops; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_line_ctrl ) (struct cardstate*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* baud_rate ) (struct cardstate*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_modem_ctrl ) (struct cardstate*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B115200 ; 
 int /*<<< orphan*/  CS8 ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_START ; 
 scalar_t__ MS_LOCKED ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gigaset_schedule_event (struct cardstate*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct cardstate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int gigaset_start(struct cardstate *cs)
{
	unsigned long flags;

	if (mutex_lock_interruptible(&cs->mutex))
		return -EBUSY;

	spin_lock_irqsave(&cs->lock, flags);
	cs->connected = 1;
	spin_unlock_irqrestore(&cs->lock, flags);

	if (cs->mstate != MS_LOCKED) {
		cs->ops->set_modem_ctrl(cs, 0, TIOCM_DTR | TIOCM_RTS);
		cs->ops->baud_rate(cs, B115200);
		cs->ops->set_line_ctrl(cs, CS8);
		cs->control_state = TIOCM_DTR | TIOCM_RTS;
	}

	cs->waiting = 1;

	if (!gigaset_add_event(cs, &cs->at_state, EV_START, NULL, 0, NULL)) {
		cs->waiting = 0;
		goto error;
	}
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	mutex_unlock(&cs->mutex);
	return 0;

error:
	mutex_unlock(&cs->mutex);
	return -ENOMEM;
}