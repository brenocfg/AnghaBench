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
struct pci_dev {unsigned char irq; } ;

/* Variables and functions */

unsigned long divasa_get_pci_irq(unsigned char bus, unsigned char func,
				 void *pci_dev_handle)
{
	unsigned char irq = 0;
	struct pci_dev *dev = (struct pci_dev *) pci_dev_handle;

	irq = dev->irq;

	return ((unsigned long) irq);
}