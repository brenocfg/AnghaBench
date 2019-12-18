#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; scalar_t__ err_log_state; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  hysdn_lock; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 scalar_t__ CARD_STATE_RUN ; 
 scalar_t__ ERRLOG_STATE_OFF ; 
 scalar_t__ ERRLOG_STATE_ON ; 
 scalar_t__ ERRLOG_STATE_START ; 
 scalar_t__ ERRLOG_STATE_STOP ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ergo_set_errlog_state(hysdn_card *card, int on)
{
	unsigned long flags;

	if (card->state != CARD_STATE_RUN) {
		card->err_log_state = ERRLOG_STATE_OFF;		/* must be off */
		return;
	}
	spin_lock_irqsave(&card->hysdn_lock, flags);

	if (((card->err_log_state == ERRLOG_STATE_OFF) && !on) ||
	    ((card->err_log_state == ERRLOG_STATE_ON) && on)) {
		spin_unlock_irqrestore(&card->hysdn_lock, flags);
		return;		/* nothing to do */
	}
	if (on)
		card->err_log_state = ERRLOG_STATE_START;	/* request start */
	else
		card->err_log_state = ERRLOG_STATE_STOP;	/* request stop */

	spin_unlock_irqrestore(&card->hysdn_lock, flags);
	schedule_work(&card->irq_queue);
}