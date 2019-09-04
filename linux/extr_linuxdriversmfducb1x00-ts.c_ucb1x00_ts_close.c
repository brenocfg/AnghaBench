#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ucb1x00_ts {TYPE_1__* ucb; scalar_t__ rtask; } ;
struct input_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ irq_base; } ;

/* Variables and functions */
 scalar_t__ UCB_IRQ_TSPX ; 
 int /*<<< orphan*/  UCB_TS_CR ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ucb1x00_ts*) ; 
 struct ucb1x00_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  ucb1x00_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucb1x00_ts_close(struct input_dev *idev)
{
	struct ucb1x00_ts *ts = input_get_drvdata(idev);

	if (ts->rtask)
		kthread_stop(ts->rtask);

	ucb1x00_enable(ts->ucb);
	free_irq(ts->ucb->irq_base + UCB_IRQ_TSPX, ts);
	ucb1x00_reg_write(ts->ucb, UCB_TS_CR, 0);
	ucb1x00_disable(ts->ucb);
}