#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci1710_private {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  mux_scan; int /*<<< orphan*/  ctrl_ext; scalar_t__ ai_et; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  pacer; scalar_t__ iobase; struct comedi_subdevice* read_subdev; int /*<<< orphan*/  attached; struct pci1710_private* private; } ;
struct comedi_cmd {int flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_WAKE_EOS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCI171X_CLRFIFO_REG ; 
 scalar_t__ PCI171X_CLRINT_REG ; 
 int /*<<< orphan*/  PCI171X_CTRL_CNT0 ; 
 scalar_t__ PCI171X_CTRL_REG ; 
 int /*<<< orphan*/  PCI171X_CTRL_SW ; 
 scalar_t__ PCI171X_MUX_REG ; 
 int PCI171X_STATUS_IRQ ; 
 scalar_t__ PCI171X_STATUS_REG ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci1710_handle_every_sample (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci1710_handle_fifo (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static irqreturn_t pci1710_irq_handler(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct pci1710_private *devpriv = dev->private;
	struct comedi_subdevice *s;
	struct comedi_cmd *cmd;

	if (!dev->attached)	/*  is device attached? */
		return IRQ_NONE;	/*  no, exit */

	s = dev->read_subdev;
	cmd = &s->async->cmd;

	/*  is this interrupt from our board? */
	if (!(inw(dev->iobase + PCI171X_STATUS_REG) & PCI171X_STATUS_IRQ))
		return IRQ_NONE;	/*  no, exit */

	if (devpriv->ai_et) {	/*  Switch from initial TRIG_EXT to TRIG_xxx. */
		devpriv->ai_et = 0;
		devpriv->ctrl &= PCI171X_CTRL_CNT0;
		devpriv->ctrl |= PCI171X_CTRL_SW; /* set software trigger */
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);
		devpriv->ctrl = devpriv->ctrl_ext;
		outb(0, dev->iobase + PCI171X_CLRFIFO_REG);
		outb(0, dev->iobase + PCI171X_CLRINT_REG);
		/* no sample on this interrupt; reset the channel interval */
		outw(devpriv->mux_scan, dev->iobase + PCI171X_MUX_REG);
		outw(devpriv->ctrl, dev->iobase + PCI171X_CTRL_REG);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		return IRQ_HANDLED;
	}

	if (cmd->flags & CMDF_WAKE_EOS)
		pci1710_handle_every_sample(dev, s);
	else
		pci1710_handle_fifo(dev, s);

	comedi_handle_events(dev, s);

	return IRQ_HANDLED;
}