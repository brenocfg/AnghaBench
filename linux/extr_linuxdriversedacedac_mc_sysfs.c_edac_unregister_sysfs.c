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
struct mem_ctl_info {int /*<<< orphan*/  dev; struct bus_type* bus; } ;
struct bus_type {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_unregister (struct bus_type*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const*) ; 

void edac_unregister_sysfs(struct mem_ctl_info *mci)
{
	struct bus_type *bus = mci->bus;
	const char *name = mci->bus->name;

	edac_dbg(1, "Unregistering device %s\n", dev_name(&mci->dev));
	device_unregister(&mci->dev);
	bus_unregister(bus);
	kfree(name);
}