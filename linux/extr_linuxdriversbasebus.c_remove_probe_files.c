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
struct bus_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_attr_drivers_autoprobe ; 
 int /*<<< orphan*/  bus_attr_drivers_probe ; 
 int /*<<< orphan*/  bus_remove_file (struct bus_type*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_probe_files(struct bus_type *bus)
{
	bus_remove_file(bus, &bus_attr_drivers_autoprobe);
	bus_remove_file(bus, &bus_attr_drivers_probe);
}