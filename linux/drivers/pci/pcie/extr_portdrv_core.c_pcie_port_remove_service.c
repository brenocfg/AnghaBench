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
struct pcie_port_service_driver {int /*<<< orphan*/  (* remove ) (struct pcie_device*) ;} ;
struct pcie_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct pcie_device*) ; 
 struct pcie_device* to_pcie_device (struct device*) ; 
 struct pcie_port_service_driver* to_service_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcie_port_remove_service(struct device *dev)
{
	struct pcie_device *pciedev;
	struct pcie_port_service_driver *driver;

	if (!dev || !dev->driver)
		return 0;

	pciedev = to_pcie_device(dev);
	driver = to_service_driver(dev->driver);
	if (driver && driver->remove) {
		driver->remove(pciedev);
		put_device(dev);
	}
	return 0;
}