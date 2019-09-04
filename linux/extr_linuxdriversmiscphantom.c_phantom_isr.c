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
typedef  unsigned int u32 ;
struct phm_regs {int mask; int* values; int /*<<< orphan*/  count; } ;
struct phantom_device {int status; int ctl_reg; int /*<<< orphan*/  wait; int /*<<< orphan*/  counter; scalar_t__ iaddr; int /*<<< orphan*/  regs_lock; scalar_t__ oaddr; struct phm_regs oregs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PHB_NOT_OH ; 
 scalar_t__ PHN_CONTROL ; 
 int PHN_CTL_AMP ; 
 unsigned int PHN_CTL_IRQ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t phantom_isr(int irq, void *data)
{
	struct phantom_device *dev = data;
	unsigned int i;
	u32 ctl;

	spin_lock(&dev->regs_lock);
	ctl = ioread32(dev->iaddr + PHN_CONTROL);
	if (!(ctl & PHN_CTL_IRQ)) {
		spin_unlock(&dev->regs_lock);
		return IRQ_NONE;
	}

	iowrite32(0, dev->iaddr);
	iowrite32(0xc0, dev->iaddr);

	if (dev->status & PHB_NOT_OH) {
		struct phm_regs *r = &dev->oregs;
		u32 m = min(r->count, 8U);

		for (i = 0; i < m; i++)
			if (r->mask & BIT(i))
				iowrite32(r->values[i], dev->oaddr + i);

		dev->ctl_reg ^= PHN_CTL_AMP;
		iowrite32(dev->ctl_reg, dev->iaddr + PHN_CONTROL);
	}
	spin_unlock(&dev->regs_lock);

	ioread32(dev->iaddr); /* PCI posting */

	atomic_inc(&dev->counter);
	wake_up_interruptible(&dev->wait);

	return IRQ_HANDLED;
}