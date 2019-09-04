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
struct ipack_bus_device {int /*<<< orphan*/  bus_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ipack_bus_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipack_bus_type ; 
 int /*<<< orphan*/  ipack_ida ; 
 int /*<<< orphan*/  ipack_unregister_bus_member ; 
 int /*<<< orphan*/  kfree (struct ipack_bus_device*) ; 

int ipack_bus_unregister(struct ipack_bus_device *bus)
{
	bus_for_each_dev(&ipack_bus_type, NULL, bus,
		ipack_unregister_bus_member);
	ida_simple_remove(&ipack_ida, bus->bus_nr);
	kfree(bus);
	return 0;
}