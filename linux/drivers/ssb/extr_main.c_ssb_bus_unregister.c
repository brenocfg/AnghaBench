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
struct ssb_bus {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  ssb_buses_lock () ; 
 int /*<<< orphan*/  ssb_buses_unlock () ; 
 int /*<<< orphan*/  ssb_devices_unregister (struct ssb_bus*) ; 
 int ssb_gpio_unregister (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_iounmap (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_pci_exit (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_pcmcia_exit (struct ssb_bus*) ; 

void ssb_bus_unregister(struct ssb_bus *bus)
{
	int err;

	err = ssb_gpio_unregister(bus);
	if (err == -EBUSY)
		pr_debug("Some GPIOs are still in use\n");
	else if (err)
		pr_debug("Can not unregister GPIO driver: %i\n", err);

	ssb_buses_lock();
	ssb_devices_unregister(bus);
	list_del(&bus->list);
	ssb_buses_unlock();

	ssb_pcmcia_exit(bus);
	ssb_pci_exit(bus);
	ssb_iounmap(bus);
}