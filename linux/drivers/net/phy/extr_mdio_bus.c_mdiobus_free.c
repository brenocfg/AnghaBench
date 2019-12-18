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
struct mii_bus {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MDIOBUS_ALLOCATED ; 
 scalar_t__ MDIOBUS_RELEASED ; 
 scalar_t__ MDIOBUS_UNREGISTERED ; 
 int /*<<< orphan*/  kfree (struct mii_bus*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void mdiobus_free(struct mii_bus *bus)
{
	/* For compatibility with error handling in drivers. */
	if (bus->state == MDIOBUS_ALLOCATED) {
		kfree(bus);
		return;
	}

	BUG_ON(bus->state != MDIOBUS_UNREGISTERED);
	bus->state = MDIOBUS_RELEASED;

	put_device(&bus->dev);
}