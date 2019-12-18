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
struct pci230_private {int hwver; int /*<<< orphan*/  ao_stop_spinlock; scalar_t__ daqio; int /*<<< orphan*/  ao_cmd_started; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct pci230_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCI230P2_DACSWTRIG ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  pci230_handle_ao_nofifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pci230_ao_inttrig_scan_begin(struct comedi_device *dev,
					struct comedi_subdevice *s,
					unsigned int trig_num)
{
	struct pci230_private *devpriv = dev->private;
	unsigned long irqflags;

	if (trig_num)
		return -EINVAL;

	spin_lock_irqsave(&devpriv->ao_stop_spinlock, irqflags);
	if (!devpriv->ao_cmd_started) {
		spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
		return 1;
	}
	/* Perform scan. */
	if (devpriv->hwver < 2) {
		/* Not using DAC FIFO. */
		spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
		pci230_handle_ao_nofifo(dev, s);
		comedi_handle_events(dev, s);
	} else {
		/* Using DAC FIFO. */
		/* Read DACSWTRIG register to trigger conversion. */
		inw(devpriv->daqio + PCI230P2_DACSWTRIG);
		spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
	}
	/* Delay.  Should driver be responsible for this? */
	/* XXX TODO: See if DAC busy bit can be used. */
	udelay(8);
	return 1;
}