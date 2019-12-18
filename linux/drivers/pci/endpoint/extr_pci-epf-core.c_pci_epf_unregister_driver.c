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
struct pci_epf_driver {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_epf_remove_cfs (struct pci_epf_driver*) ; 

void pci_epf_unregister_driver(struct pci_epf_driver *driver)
{
	pci_epf_remove_cfs(driver);
	driver_unregister(&driver->driver);
}