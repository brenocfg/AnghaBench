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
struct bcma_bus {int /*<<< orphan*/  drv_cc_b; int /*<<< orphan*/  drv_cc; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  bcma_core_chipcommon_b_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,...) ; 
 int bcma_gpio_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_unregister_cores (struct bcma_bus*) ; 

void bcma_bus_unregister(struct bcma_bus *bus)
{
	int err;

	err = bcma_gpio_unregister(&bus->drv_cc);
	if (err == -EBUSY)
		bcma_err(bus, "Some GPIOs are still in use.\n");
	else if (err)
		bcma_err(bus, "Can not unregister GPIO driver: %i\n", err);

	bcma_core_chipcommon_b_free(&bus->drv_cc_b);

	bcma_unregister_cores(bus);
}