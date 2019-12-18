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
struct pci1710_private {int /*<<< orphan*/  ctrl; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pci1710_private* private; } ;

/* Variables and functions */
 scalar_t__ PCI171X_CLRFIFO_REG ; 
 scalar_t__ PCI171X_CLRINT_REG ; 
 int /*<<< orphan*/  PCI171X_CTRL_CNT0 ; 
 scalar_t__ PCI171X_CTRL_REG ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pci1710_ai_cancel(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	struct pci1710_private *devpriv = dev->private;

	/* disable A/D triggers and interrupt sources */
	devpriv->ctrl &= PCI171X_CTRL_CNT0;	/* preserve counter 0 clk src */
	outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);

	/* disable pacer */
	comedi_8254_pacer_enable(dev->pacer, 1, 2, false);

	/* clear A/D FIFO and any pending interrutps */
	outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
	outb(0, dev->iobase + PCI171X_CLRINT_REG);

	return 0;
}