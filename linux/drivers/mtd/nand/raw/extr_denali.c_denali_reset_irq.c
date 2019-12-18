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
struct denali_controller {int /*<<< orphan*/  irq_lock; scalar_t__ irq_mask; scalar_t__ irq_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void denali_reset_irq(struct denali_controller *denali)
{
	unsigned long flags;

	spin_lock_irqsave(&denali->irq_lock, flags);
	denali->irq_status = 0;
	denali->irq_mask = 0;
	spin_unlock_irqrestore(&denali->irq_lock, flags);
}