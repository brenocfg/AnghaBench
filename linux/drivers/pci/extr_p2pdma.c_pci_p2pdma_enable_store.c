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
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct device* bus_find_device_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  iscntrl (char const) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,char const*) ; 
 int /*<<< orphan*/  pci_has_p2pmem (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,int,char const*) ; 
 scalar_t__ strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strtobool (char const*,int*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

int pci_p2pdma_enable_store(const char *page, struct pci_dev **p2p_dev,
			    bool *use_p2pdma)
{
	struct device *dev;

	dev = bus_find_device_by_name(&pci_bus_type, NULL, page);
	if (dev) {
		*use_p2pdma = true;
		*p2p_dev = to_pci_dev(dev);

		if (!pci_has_p2pmem(*p2p_dev)) {
			pci_err(*p2p_dev,
				"PCI device has no peer-to-peer memory: %s\n",
				page);
			pci_dev_put(*p2p_dev);
			return -ENODEV;
		}

		return 0;
	} else if ((page[0] == '0' || page[0] == '1') && !iscntrl(page[1])) {
		/*
		 * If the user enters a PCI device that  doesn't exist
		 * like "0000:01:00.1", we don't want strtobool to think
		 * it's a '0' when it's clearly not what the user wanted.
		 * So we require 0's and 1's to be exactly one character.
		 */
	} else if (!strtobool(page, use_p2pdma)) {
		return 0;
	}

	pr_err("No such PCI device: %.*s\n", (int)strcspn(page, "\n"), page);
	return -ENODEV;
}