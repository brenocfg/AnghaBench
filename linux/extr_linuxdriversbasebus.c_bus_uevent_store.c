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
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ subsys; } ;

/* Variables and functions */
 int kobject_synth_uevent (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static ssize_t bus_uevent_store(struct bus_type *bus,
				const char *buf, size_t count)
{
	int rc;

	rc = kobject_synth_uevent(&bus->p->subsys.kobj, buf, count);
	return rc ? rc : count;
}