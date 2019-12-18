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
struct mii_bus {int* mdio_map; } ;

/* Variables and functions */

bool mdiobus_is_registered_device(struct mii_bus *bus, int addr)
{
	return bus->mdio_map[addr];
}