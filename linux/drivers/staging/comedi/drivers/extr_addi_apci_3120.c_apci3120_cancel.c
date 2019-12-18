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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct apci3120_private* private; } ;
struct apci3120_private {scalar_t__ cur_dmabuf; scalar_t__ mode; scalar_t__ ctrl; scalar_t__ amcc; scalar_t__ addon; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMCC_OP_REG_AGCSTS ; 
 scalar_t__ AMCC_OP_REG_MCSR ; 
 scalar_t__ APCI3120_CTRL_REG ; 
 scalar_t__ APCI3120_MODE_REG ; 
 scalar_t__ APCI3120_STATUS_REG ; 
 int /*<<< orphan*/  apci3120_addon_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int apci3120_cancel(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	struct apci3120_private *devpriv = dev->private;

	/* Add-On - disable DMA */
	outw(0, devpriv->addon + 4);

	/* Add-On - disable bus master */
	apci3120_addon_write(dev, 0, AMCC_OP_REG_AGCSTS);

	/* AMCC - disable bus master */
	outl(0, devpriv->amcc + AMCC_OP_REG_MCSR);

	/* disable all counters, ext trigger, and reset scan */
	devpriv->ctrl = 0;
	outw(devpriv->ctrl, dev->iobase + APCI3120_CTRL_REG);

	/* DISABLE_ALL_INTERRUPT */
	devpriv->mode = 0;
	outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);

	inw(dev->iobase + APCI3120_STATUS_REG);
	devpriv->cur_dmabuf = 0;

	return 0;
}