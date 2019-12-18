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
struct pci230_private {int /*<<< orphan*/  ai_stop_spinlock; scalar_t__ ai_cmd_started; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct pci230_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GAT_GND ; 
 int /*<<< orphan*/  GAT_VCC ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 unsigned char pci230_gat_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci230_ai_inttrig_scan_begin(struct comedi_device *dev,
					struct comedi_subdevice *s,
					unsigned int trig_num)
{
	struct pci230_private *devpriv = dev->private;
	unsigned long irqflags;
	unsigned char zgat;

	if (trig_num)
		return -EINVAL;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	if (devpriv->ai_cmd_started) {
		/* Trigger scan by waggling CT0 gate source. */
		zgat = pci230_gat_config(0, GAT_GND);
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
		zgat = pci230_gat_config(0, GAT_VCC);
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
	}
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);

	return 1;
}