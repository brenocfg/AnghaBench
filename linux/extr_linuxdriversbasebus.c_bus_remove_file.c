#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bus_type {TYPE_2__* p; } ;
struct bus_attribute {int /*<<< orphan*/  attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ subsys; } ;

/* Variables and functions */
 scalar_t__ bus_get (struct bus_type*) ; 
 int /*<<< orphan*/  bus_put (struct bus_type*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bus_remove_file(struct bus_type *bus, struct bus_attribute *attr)
{
	if (bus_get(bus)) {
		sysfs_remove_file(&bus->p->subsys.kobj, &attr->attr);
		bus_put(bus);
	}
}