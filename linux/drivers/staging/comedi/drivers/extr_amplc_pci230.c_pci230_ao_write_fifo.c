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
struct pci230_private {scalar_t__ daqio; } ;
struct comedi_device {struct pci230_private* private; } ;

/* Variables and functions */
 scalar_t__ PCI230P2_DACDATA ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_mangle_datum (struct comedi_device*,unsigned short) ; 

__attribute__((used)) static void pci230_ao_write_fifo(struct comedi_device *dev,
				 unsigned short datum, unsigned int chan)
{
	struct pci230_private *devpriv = dev->private;

	/* Write mangled datum to appropriate DACDATA register. */
	outw(pci230_ao_mangle_datum(dev, datum),
	     devpriv->daqio + PCI230P2_DACDATA);
}