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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ device_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_cfg_access_trylock (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (struct pci_dev*) ; 

__attribute__((used)) static int pci_dev_trylock(struct pci_dev *dev)
{
	if (pci_cfg_access_trylock(dev)) {
		if (device_trylock(&dev->dev))
			return 1;
		pci_cfg_access_unlock(dev);
	}

	return 0;
}