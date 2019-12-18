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
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_next_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

int no_pci_devices(void)
{
	struct device *dev;
	int no_devices;

	dev = bus_find_next_device(&pci_bus_type, NULL);
	no_devices = (dev == NULL);
	put_device(dev);
	return no_devices;
}