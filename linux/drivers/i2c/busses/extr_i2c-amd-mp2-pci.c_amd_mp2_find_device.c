#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
struct amd_mp2_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 TYPE_1__ amd_mp2_pci_driver ; 
 struct device* driver_find_next_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

struct amd_mp2_dev *amd_mp2_find_device(void)
{
	struct device *dev;
	struct pci_dev *pci_dev;

	dev = driver_find_next_device(&amd_mp2_pci_driver.driver, NULL);
	if (!dev)
		return NULL;

	pci_dev = to_pci_dev(dev);
	return (struct amd_mp2_dev *)pci_get_drvdata(pci_dev);
}