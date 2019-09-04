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
struct edp_ctrl {int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EDP_INTR_MASK1 ; 
 int EDP_INTR_MASK2 ; 
 scalar_t__ REG_EDP_INTERRUPT_REG_1 ; 
 scalar_t__ REG_EDP_INTERRUPT_REG_2 ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void edp_ctrl_irq_enable(struct edp_ctrl *ctrl, int enable)
{
	unsigned long flags;

	DBG("%d", enable);
	spin_lock_irqsave(&ctrl->irq_lock, flags);
	if (enable) {
		edp_write(ctrl->base + REG_EDP_INTERRUPT_REG_1, EDP_INTR_MASK1);
		edp_write(ctrl->base + REG_EDP_INTERRUPT_REG_2, EDP_INTR_MASK2);
	} else {
		edp_write(ctrl->base + REG_EDP_INTERRUPT_REG_1, 0x0);
		edp_write(ctrl->base + REG_EDP_INTERRUPT_REG_2, 0x0);
	}
	spin_unlock_irqrestore(&ctrl->irq_lock, flags);
	DBG("exit");
}