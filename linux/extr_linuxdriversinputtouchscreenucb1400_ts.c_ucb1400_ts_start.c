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
struct ucb1400_ts {int stopped; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  ucb1400_ts_irq_enable (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  ucb1400_ts_mode_int (struct ucb1400_ts*) ; 

__attribute__((used)) static void ucb1400_ts_start(struct ucb1400_ts *ucb)
{
	/* Tell IRQ thread that it may poll the device. */
	ucb->stopped = false;
	mb();

	ucb1400_ts_mode_int(ucb);
	ucb1400_ts_irq_enable(ucb);

	enable_irq(ucb->irq);
}