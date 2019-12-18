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
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ pci_match_one_device (struct pci_device_id const*,struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int match_pci_dev_by_id(struct device *dev, const void *data)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	const struct pci_device_id *id = data;

	if (pci_match_one_device(id, pdev))
		return 1;
	return 0;
}