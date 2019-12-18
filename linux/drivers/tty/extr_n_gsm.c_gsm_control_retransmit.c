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
struct timer_list {int dummy; } ;
struct gsm_mux {scalar_t__ cretries; int t2; int /*<<< orphan*/  control_lock; int /*<<< orphan*/  t2_timer; int /*<<< orphan*/  event; struct gsm_control* pending_cmd; } ;
struct gsm_control {int done; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int HZ ; 
 struct gsm_mux* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct gsm_mux* gsm ; 
 int /*<<< orphan*/  gsm_control_transmit (struct gsm_mux*,struct gsm_control*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  t2_timer ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gsm_control_retransmit(struct timer_list *t)
{
	struct gsm_mux *gsm = from_timer(gsm, t, t2_timer);
	struct gsm_control *ctrl;
	unsigned long flags;
	spin_lock_irqsave(&gsm->control_lock, flags);
	ctrl = gsm->pending_cmd;
	if (ctrl) {
		gsm->cretries--;
		if (gsm->cretries == 0) {
			gsm->pending_cmd = NULL;
			ctrl->error = -ETIMEDOUT;
			ctrl->done = 1;
			spin_unlock_irqrestore(&gsm->control_lock, flags);
			wake_up(&gsm->event);
			return;
		}
		gsm_control_transmit(gsm, ctrl);
		mod_timer(&gsm->t2_timer, jiffies + gsm->t2 * HZ / 100);
	}
	spin_unlock_irqrestore(&gsm->control_lock, flags);
}