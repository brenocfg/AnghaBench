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
struct pcidas64_private {scalar_t__ main_iobase; scalar_t__ plx9080_iobase; } ;
struct comedi_device {scalar_t__ mmio; scalar_t__ irq; struct pcidas64_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cb_pcidas64_free_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_pci_disable (struct comedi_device*) ; 
 int /*<<< orphan*/  disable_plx_interrupts (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void detach(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;

	if (dev->irq)
		free_irq(dev->irq, dev);
	if (devpriv) {
		if (devpriv->plx9080_iobase) {
			disable_plx_interrupts(dev);
			iounmap(devpriv->plx9080_iobase);
		}
		if (devpriv->main_iobase)
			iounmap(devpriv->main_iobase);
		if (dev->mmio)
			iounmap(dev->mmio);
	}
	comedi_pci_disable(dev);
	cb_pcidas64_free_dma(dev);
}