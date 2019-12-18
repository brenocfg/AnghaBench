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
struct pci_hba_data {int dummy; } ;
struct device {struct pci_hba_data* platform_data; struct device* parent; } ;

/* Variables and functions */
 scalar_t__ likely (struct pci_hba_data*) ; 

__attribute__((used)) static inline struct pci_hba_data *parisc_walk_tree(struct device *dev)
{
	struct device *otherdev;

	if (likely(dev->platform_data))
		return dev->platform_data;

	/* OK, just traverse the bus to find it */
	for (otherdev = dev->parent;
	     otherdev;
	     otherdev = otherdev->parent) {
		if (otherdev->platform_data) {
			dev->platform_data = otherdev->platform_data;
			break;
		}
	}

	return dev->platform_data;
}