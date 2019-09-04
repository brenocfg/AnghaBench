#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bus_type {int dummy; } ;
struct attribute_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int subsys_register (struct bus_type*,struct attribute_group const**,int /*<<< orphan*/ *) ; 
 TYPE_1__* system_kset ; 

int subsys_system_register(struct bus_type *subsys,
			   const struct attribute_group **groups)
{
	return subsys_register(subsys, groups, &system_kset->kobj);
}