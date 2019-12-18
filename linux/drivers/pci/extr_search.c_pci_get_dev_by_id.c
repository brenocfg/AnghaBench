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
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct device* bus_find_device (int /*<<< orphan*/ *,struct device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  match_pci_dev_by_id ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct pci_dev *pci_get_dev_by_id(const struct pci_device_id *id,
					 struct pci_dev *from)
{
	struct device *dev;
	struct device *dev_start = NULL;
	struct pci_dev *pdev = NULL;

	WARN_ON(in_interrupt());
	if (from)
		dev_start = &from->dev;
	dev = bus_find_device(&pci_bus_type, dev_start, (void *)id,
			      match_pci_dev_by_id);
	if (dev)
		pdev = to_pci_dev(dev);
	pci_dev_put(from);
	return pdev;
}