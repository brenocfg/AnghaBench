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
struct TYPE_2__ {int /*<<< orphan*/ * pm; } ;
struct pci_driver {TYPE_1__ driver; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int pci_register_driver (struct pci_driver*) ; 
 int /*<<< orphan*/  ssb_pcihost_pm_ops ; 
 int /*<<< orphan*/  ssb_pcihost_probe ; 
 int /*<<< orphan*/  ssb_pcihost_remove ; 

int ssb_pcihost_register(struct pci_driver *driver)
{
	driver->probe = ssb_pcihost_probe;
	driver->remove = ssb_pcihost_remove;
#ifdef CONFIG_PM_SLEEP
	driver->driver.pm = &ssb_pcihost_pm_ops;
#endif

	return pci_register_driver(driver);
}