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
struct pci_dev {int irq; } ;
struct mcb_device {struct mcb_bus* bus; } ;
struct mcb_bus {struct device* carrier; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int mcb_pci_get_irq(struct mcb_device *mdev)
{
	struct mcb_bus *mbus = mdev->bus;
	struct device *dev = mbus->carrier;
	struct pci_dev *pdev = to_pci_dev(dev);

	return pdev->irq;
}