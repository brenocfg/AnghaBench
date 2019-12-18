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
struct ucb1x00_ts {int /*<<< orphan*/ * rtask; TYPE_1__* ucb; int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; int /*<<< orphan*/  irq_wait; scalar_t__ irq_disabled; } ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ irq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 int EFAULT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ UCB_IRQ_TSPX ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ucb1x00_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct ucb1x00_ts*,char*) ; 
 scalar_t__ machine_is_collie () ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,unsigned long,char*,struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  ucb1x00_adc_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_adc_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_thread ; 
 int /*<<< orphan*/  ucb1x00_ts_irq ; 
 int /*<<< orphan*/  ucb1x00_ts_read_xres (struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  ucb1x00_ts_read_yres (struct ucb1x00_ts*) ; 

__attribute__((used)) static int ucb1x00_ts_open(struct input_dev *idev)
{
	struct ucb1x00_ts *ts = input_get_drvdata(idev);
	unsigned long flags = 0;
	int ret = 0;

	BUG_ON(ts->rtask);

	if (machine_is_collie())
		flags = IRQF_TRIGGER_RISING;
	else
		flags = IRQF_TRIGGER_FALLING;

	ts->irq_disabled = 0;

	init_waitqueue_head(&ts->irq_wait);
	ret = request_irq(ts->ucb->irq_base + UCB_IRQ_TSPX, ucb1x00_ts_irq,
			  flags, "ucb1x00-ts", ts);
	if (ret < 0)
		goto out;

	/*
	 * If we do this at all, we should allow the user to
	 * measure and read the X and Y resistance at any time.
	 */
	ucb1x00_adc_enable(ts->ucb);
	ts->x_res = ucb1x00_ts_read_xres(ts);
	ts->y_res = ucb1x00_ts_read_yres(ts);
	ucb1x00_adc_disable(ts->ucb);

	ts->rtask = kthread_run(ucb1x00_thread, ts, "ktsd");
	if (!IS_ERR(ts->rtask)) {
		ret = 0;
	} else {
		free_irq(ts->ucb->irq_base + UCB_IRQ_TSPX, ts);
		ts->rtask = NULL;
		ret = -EFAULT;
	}

 out:
	return ret;
}