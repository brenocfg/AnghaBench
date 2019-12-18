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
struct altr_i2c_dev {int isr_status; int isr_mask; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ALTR_I2C_ISR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t altr_i2c_isr_quick(int irq, void *_dev)
{
	struct altr_i2c_dev *idev = _dev;
	irqreturn_t ret = IRQ_HANDLED;

	/* Read IRQ status but only interested in Enabled IRQs. */
	idev->isr_status = readl(idev->base + ALTR_I2C_ISR) & idev->isr_mask;
	if (idev->isr_status)
		ret = IRQ_WAKE_THREAD;

	return ret;
}