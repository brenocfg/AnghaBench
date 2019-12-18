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
struct ni_private {int /*<<< orphan*/  mite; int /*<<< orphan*/ * gpct_mite_ring; int /*<<< orphan*/  cdo_mite_ring; int /*<<< orphan*/  ao_mite_ring; int /*<<< orphan*/  ai_mite_ring; } ;
struct comedi_device {scalar_t__ mmio; scalar_t__ irq; struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (struct comedi_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mio_common_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  mite_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_free_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcimio_detach(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;

	mio_common_detach(dev);
	if (dev->irq)
		free_irq(dev->irq, dev);
	if (devpriv) {
		mite_free_ring(devpriv->ai_mite_ring);
		mite_free_ring(devpriv->ao_mite_ring);
		mite_free_ring(devpriv->cdo_mite_ring);
		mite_free_ring(devpriv->gpct_mite_ring[0]);
		mite_free_ring(devpriv->gpct_mite_ring[1]);
		mite_detach(devpriv->mite);
	}
	if (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disable(dev);
}