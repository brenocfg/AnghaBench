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
typedef  int u16 ;
struct ace_device {int in_irq; scalar_t__ fsm_task; scalar_t__ fsm_state; int data_count; int fsm_continue_flag; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  data_result; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_CTRL ; 
 int ACE_CTRL_RESETIRQ ; 
 int /*<<< orphan*/  ACE_SECCNTCMD ; 
 int /*<<< orphan*/  ACE_STATUS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ace_fsm_dostate (struct ace_device*) ; 
 int ace_in (struct ace_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ace_in32 (struct ace_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ace_interrupt_checkstate (struct ace_device*) ; 
 int /*<<< orphan*/  ace_out (struct ace_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ace_interrupt(int irq, void *dev_id)
{
	u16 creg;
	struct ace_device *ace = dev_id;

	/* be safe and get the lock */
	spin_lock(&ace->lock);
	ace->in_irq = 1;

	/* clear the interrupt */
	creg = ace_in(ace, ACE_CTRL);
	ace_out(ace, ACE_CTRL, creg | ACE_CTRL_RESETIRQ);
	ace_out(ace, ACE_CTRL, creg);

	/* check for IO failures */
	if (ace_interrupt_checkstate(ace))
		ace->data_result = -EIO;

	if (ace->fsm_task == 0) {
		dev_err(ace->dev,
			"spurious irq; stat=%.8x ctrl=%.8x cmd=%.4x\n",
			ace_in32(ace, ACE_STATUS), ace_in32(ace, ACE_CTRL),
			ace_in(ace, ACE_SECCNTCMD));
		dev_err(ace->dev, "fsm_task=%i fsm_state=%i data_count=%i\n",
			ace->fsm_task, ace->fsm_state, ace->data_count);
	}

	/* Loop over state machine until told to stop */
	ace->fsm_continue_flag = 1;
	while (ace->fsm_continue_flag)
		ace_fsm_dostate(ace);

	/* done with interrupt; drop the lock */
	ace->in_irq = 0;
	spin_unlock(&ace->lock);

	return IRQ_HANDLED;
}