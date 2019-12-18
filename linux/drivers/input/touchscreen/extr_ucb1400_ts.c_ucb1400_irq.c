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
struct ucb1400_ts {int irq; int /*<<< orphan*/  stopped; int /*<<< orphan*/  ts_idev; int /*<<< orphan*/  ts_wait; int /*<<< orphan*/  ac97; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  UCB1400_TS_POLL_PERIOD ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_adc_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_adc_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_clear_pending_irq (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  ucb1400_ts_event_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_ts_irq_enable (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  ucb1400_ts_mode_int (struct ucb1400_ts*) ; 
 int ucb1400_ts_pen_up (struct ucb1400_ts*) ; 
 unsigned int ucb1400_ts_read_pressure (struct ucb1400_ts*) ; 
 unsigned int ucb1400_ts_read_xpos (struct ucb1400_ts*) ; 
 unsigned int ucb1400_ts_read_ypos (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  ucb1400_ts_report_event (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ucb1400_irq(int irqnr, void *devid)
{
	struct ucb1400_ts *ucb = devid;
	unsigned int x, y, p;
	bool penup;

	if (unlikely(irqnr != ucb->irq))
		return IRQ_NONE;

	ucb1400_clear_pending_irq(ucb);

	/* Start with a small delay before checking pendown state */
	msleep(UCB1400_TS_POLL_PERIOD);

	while (!ucb->stopped && !(penup = ucb1400_ts_pen_up(ucb))) {

		ucb1400_adc_enable(ucb->ac97);
		x = ucb1400_ts_read_xpos(ucb);
		y = ucb1400_ts_read_ypos(ucb);
		p = ucb1400_ts_read_pressure(ucb);
		ucb1400_adc_disable(ucb->ac97);

		ucb1400_ts_report_event(ucb->ts_idev, p, x, y);

		wait_event_timeout(ucb->ts_wait, ucb->stopped,
				   msecs_to_jiffies(UCB1400_TS_POLL_PERIOD));
	}

	ucb1400_ts_event_release(ucb->ts_idev);

	if (!ucb->stopped) {
		/* Switch back to interrupt mode. */
		ucb1400_ts_mode_int(ucb);
		ucb1400_ts_irq_enable(ucb);
	}

	return IRQ_HANDLED;
}