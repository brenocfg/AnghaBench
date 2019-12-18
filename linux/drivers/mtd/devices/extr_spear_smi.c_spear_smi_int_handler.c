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
typedef  int /*<<< orphan*/  u32 ;
struct spear_smi {int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  status; scalar_t__ io_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SMI_SR ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t spear_smi_int_handler(int irq, void *dev_id)
{
	u32 status = 0;
	struct spear_smi *dev = dev_id;

	status = readl(dev->io_base + SMI_SR);

	if (unlikely(!status))
		return IRQ_NONE;

	/* clear all interrupt conditions */
	writel(0, dev->io_base + SMI_SR);

	/* copy the status register in dev->status */
	dev->status |= status;

	/* send the completion */
	wake_up_interruptible(&dev->cmd_complete);

	return IRQ_HANDLED;
}