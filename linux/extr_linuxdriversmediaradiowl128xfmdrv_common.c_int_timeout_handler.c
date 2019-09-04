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
struct timer_list {int dummy; } ;
struct fm_irq {scalar_t__ retry; scalar_t__ stage; } ;
struct fmdev {struct fm_irq irq_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ FM_IRQ_TIMEOUT_RETRY_MAX ; 
 int /*<<< orphan*/  FM_SEND_INTMSK_CMD_IDX ; 
 int /*<<< orphan*/  fm_irq_call_stage (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 struct fmdev* from_timer (struct fmdev*,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ irq_info ; 

__attribute__((used)) static void int_timeout_handler(struct timer_list *t)
{
	struct fmdev *fmdev;
	struct fm_irq *fmirq;

	fmdbg("irq: timeout,trying to re-enable fm interrupts\n");
	fmdev = from_timer(fmdev, t, irq_info.timer);
	fmirq = &fmdev->irq_info;
	fmirq->retry++;

	if (fmirq->retry > FM_IRQ_TIMEOUT_RETRY_MAX) {
		/* Stop recovery action (interrupt reenable process) and
		 * reset stage index & retry count values */
		fmirq->stage = 0;
		fmirq->retry = 0;
		fmerr("Recovery action failed duringirq processing, max retry reached\n");
		return;
	}
	fm_irq_call_stage(fmdev, FM_SEND_INTMSK_CMD_IDX);
}