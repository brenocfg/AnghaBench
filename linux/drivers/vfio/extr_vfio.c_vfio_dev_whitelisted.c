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
struct pci_dev {scalar_t__ hdr_type; } ;
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 scalar_t__ match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  vfio_driver_whitelist ; 

__attribute__((used)) static bool vfio_dev_whitelisted(struct device *dev, struct device_driver *drv)
{
	if (dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(dev);

		if (pdev->hdr_type != PCI_HEADER_TYPE_NORMAL)
			return true;
	}

	return match_string(vfio_driver_whitelist,
			    ARRAY_SIZE(vfio_driver_whitelist),
			    drv->name) >= 0;
}