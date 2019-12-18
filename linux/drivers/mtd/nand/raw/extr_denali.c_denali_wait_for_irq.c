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
typedef  int u32 ;
struct denali_controller {int irq_status; int irq_mask; int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 denali_wait_for_irq(struct denali_controller *denali, u32 irq_mask)
{
	unsigned long time_left, flags;
	u32 irq_status;

	spin_lock_irqsave(&denali->irq_lock, flags);

	irq_status = denali->irq_status;

	if (irq_mask & irq_status) {
		/* return immediately if the IRQ has already happened. */
		spin_unlock_irqrestore(&denali->irq_lock, flags);
		return irq_status;
	}

	denali->irq_mask = irq_mask;
	reinit_completion(&denali->complete);
	spin_unlock_irqrestore(&denali->irq_lock, flags);

	time_left = wait_for_completion_timeout(&denali->complete,
						msecs_to_jiffies(1000));
	if (!time_left) {
		dev_err(denali->dev, "timeout while waiting for irq 0x%x\n",
			irq_mask);
		return 0;
	}

	return denali->irq_status;
}