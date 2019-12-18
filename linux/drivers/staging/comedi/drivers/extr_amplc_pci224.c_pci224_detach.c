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
struct pci224_private {int /*<<< orphan*/  ao_scan_order; int /*<<< orphan*/  ao_scan_vals; } ;
struct comedi_device {struct pci224_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_detach (struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci224_detach(struct comedi_device *dev)
{
	struct pci224_private *devpriv = dev->private;

	comedi_pci_detach(dev);
	if (devpriv) {
		kfree(devpriv->ao_scan_vals);
		kfree(devpriv->ao_scan_order);
	}
}