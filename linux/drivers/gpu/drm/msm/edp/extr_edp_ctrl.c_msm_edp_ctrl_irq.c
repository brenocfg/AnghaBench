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
struct edp_ctrl {int /*<<< orphan*/  aux; int /*<<< orphan*/  idle_comp; int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int EDP_INTERRUPT_REG_1_HPD ; 
 int EDP_INTERRUPT_REG_2_IDLE_PATTERNs_SENT ; 
 int EDP_INTERRUPT_REG_2_READY_FOR_VIDEO ; 
 int EDP_INTR_MASK1 ; 
 int EDP_INTR_MASK2 ; 
 int EDP_INTR_STATUS1 ; 
 int EDP_INTR_STATUS2 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_EDP_INTERRUPT_REG_1 ; 
 scalar_t__ REG_EDP_INTERRUPT_REG_2 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int edp_read (scalar_t__) ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int) ; 
 int /*<<< orphan*/  msm_edp_aux_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

irqreturn_t msm_edp_ctrl_irq(struct edp_ctrl *ctrl)
{
	u32 isr1, isr2, mask1, mask2;
	u32 ack;

	DBG("");
	spin_lock(&ctrl->irq_lock);
	isr1 = edp_read(ctrl->base + REG_EDP_INTERRUPT_REG_1);
	isr2 = edp_read(ctrl->base + REG_EDP_INTERRUPT_REG_2);

	mask1 = isr1 & EDP_INTR_MASK1;
	mask2 = isr2 & EDP_INTR_MASK2;

	isr1 &= ~mask1;	/* remove masks bit */
	isr2 &= ~mask2;

	DBG("isr=%x mask=%x isr2=%x mask2=%x",
			isr1, mask1, isr2, mask2);

	ack = isr1 & EDP_INTR_STATUS1;
	ack <<= 1;	/* ack bits */
	ack |= mask1;
	edp_write(ctrl->base + REG_EDP_INTERRUPT_REG_1, ack);

	ack = isr2 & EDP_INTR_STATUS2;
	ack <<= 1;	/* ack bits */
	ack |= mask2;
	edp_write(ctrl->base + REG_EDP_INTERRUPT_REG_2, ack);
	spin_unlock(&ctrl->irq_lock);

	if (isr1 & EDP_INTERRUPT_REG_1_HPD)
		DBG("edp_hpd");

	if (isr2 & EDP_INTERRUPT_REG_2_READY_FOR_VIDEO)
		DBG("edp_video_ready");

	if (isr2 & EDP_INTERRUPT_REG_2_IDLE_PATTERNs_SENT) {
		DBG("idle_patterns_sent");
		complete(&ctrl->idle_comp);
	}

	msm_edp_aux_irq(ctrl->aux, isr1);

	return IRQ_HANDLED;
}