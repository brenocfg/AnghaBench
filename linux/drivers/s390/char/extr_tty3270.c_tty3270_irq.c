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
struct tty3270 {int attn; int /*<<< orphan*/  update_flags; int /*<<< orphan*/  hanglet; int /*<<< orphan*/  view; int /*<<< orphan*/  throttle; } ;
struct raw3270_request {int /*<<< orphan*/  rescnt; int /*<<< orphan*/  rc; } ;
struct TYPE_4__ {int dstat; int /*<<< orphan*/  count; } ;
struct TYPE_3__ {TYPE_2__ cmd; } ;
struct irb {TYPE_1__ scsw; } ;

/* Variables and functions */
 int DEV_STAT_ATTENTION ; 
 int DEV_STAT_DEV_END ; 
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  TTY_UPDATE_ALL ; 
 int /*<<< orphan*/  raw3270_get_view (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty3270_issue_read (struct tty3270*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 

__attribute__((used)) static void
tty3270_irq(struct tty3270 *tp, struct raw3270_request *rq, struct irb *irb)
{
	/* Handle ATTN. Schedule tasklet to read aid. */
	if (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		if (!tp->throttle)
			tty3270_issue_read(tp, 0);
		else
			tp->attn = 1;
	}

	if (rq) {
		if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
			rq->rc = -EIO;
			raw3270_get_view(&tp->view);
			tasklet_schedule(&tp->hanglet);
		} else {
			/* Normal end. Copy residual count. */
			rq->rescnt = irb->scsw.cmd.count;
		}
	} else if (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) {
		/* Interrupt without an outstanding request -> update all */
		tp->update_flags = TTY_UPDATE_ALL;
		tty3270_set_timer(tp, 1);
	}
}