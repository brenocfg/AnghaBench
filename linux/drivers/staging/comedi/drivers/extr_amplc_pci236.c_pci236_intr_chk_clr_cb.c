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
struct pc236_private {int /*<<< orphan*/  enable_irq; scalar_t__ lcr_iobase; } ;
struct comedi_device {struct pc236_private* private; } ;

/* Variables and functions */
 scalar_t__ PLX9052_INTCSR ; 
 int PLX9052_INTCSR_LI1STAT ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  pci236_intr_update_cb (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pci236_intr_chk_clr_cb(struct comedi_device *dev)
{
	struct pc236_private *devpriv = dev->private;

	/* check if interrupt occurred */
	if (!(inl(devpriv->lcr_iobase + PLX9052_INTCSR) &
	      PLX9052_INTCSR_LI1STAT))
		return false;
	/* clear the interrupt */
	pci236_intr_update_cb(dev, devpriv->enable_irq);
	return true;
}