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
struct ucb1400_ts {int stopped; int /*<<< orphan*/  ac97; int /*<<< orphan*/  irq; int /*<<< orphan*/  ts_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_TS_CR ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  ucb1400_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_ts_irq_disable (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucb1400_ts_stop(struct ucb1400_ts *ucb)
{
	/* Signal IRQ thread to stop polling and disable the handler. */
	ucb->stopped = true;
	mb();
	wake_up(&ucb->ts_wait);
	disable_irq(ucb->irq);

	ucb1400_ts_irq_disable(ucb);
	ucb1400_reg_write(ucb->ac97, UCB_TS_CR, 0);
}