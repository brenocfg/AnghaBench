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
struct stm32_dcmi {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  regs; int /*<<< orphan*/  misr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCMI_ICR ; 
 int /*<<< orphan*/  DCMI_MIS ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int IT_ERR ; 
 int IT_FRAME ; 
 int IT_OVR ; 
 int /*<<< orphan*/  reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t dcmi_irq_callback(int irq, void *arg)
{
	struct stm32_dcmi *dcmi = arg;
	unsigned long flags;

	spin_lock_irqsave(&dcmi->irqlock, flags);

	dcmi->misr = reg_read(dcmi->regs, DCMI_MIS);

	/* Clear interrupt */
	reg_set(dcmi->regs, DCMI_ICR, IT_FRAME | IT_OVR | IT_ERR);

	spin_unlock_irqrestore(&dcmi->irqlock, flags);

	return IRQ_WAKE_THREAD;
}