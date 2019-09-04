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
struct ucb1x00_ts {int irq_disabled; int /*<<< orphan*/  irq_wait; int /*<<< orphan*/  irq_lock; TYPE_1__* ucb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ irq_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ UCB_IRQ_TSPX ; 
 int /*<<< orphan*/  disable_irq_nosync (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ucb1x00_ts_irq(int irq, void *id)
{
	struct ucb1x00_ts *ts = id;

	spin_lock(&ts->irq_lock);
	ts->irq_disabled = 1;
	disable_irq_nosync(ts->ucb->irq_base + UCB_IRQ_TSPX);
	spin_unlock(&ts->irq_lock);
	wake_up(&ts->irq_wait);

	return IRQ_HANDLED;
}