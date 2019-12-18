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
struct ni_660x_private {int /*<<< orphan*/  mite; int /*<<< orphan*/  counter_dev; } ;
struct comedi_device {scalar_t__ mmio; scalar_t__ irq; struct ni_660x_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI660X_GLOBAL_INT_CFG ; 
 int /*<<< orphan*/  comedi_pci_disable (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mite_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_660x_free_mite_rings (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_660x_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_gpct_device_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_660x_detach(struct comedi_device *dev)
{
	struct ni_660x_private *devpriv = dev->private;

	if (dev->irq) {
		ni_660x_write(dev, 0, 0, NI660X_GLOBAL_INT_CFG);
		free_irq(dev->irq, dev);
	}
	if (devpriv) {
		ni_gpct_device_destroy(devpriv->counter_dev);
		ni_660x_free_mite_rings(dev);
		mite_detach(devpriv->mite);
	}
	if (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disable(dev);
}