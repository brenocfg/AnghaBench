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
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;
struct thermal_zone_device {TYPE_2__ trips_attribute_group; int /*<<< orphan*/  trip_hyst_attrs; TYPE_1__* ops; int /*<<< orphan*/  trip_temp_attrs; int /*<<< orphan*/  trip_type_attrs; } ;
struct TYPE_3__ {scalar_t__ get_trip_hyst; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_trip_attrs(struct thermal_zone_device *tz)
{
	if (!tz)
		return;

	kfree(tz->trip_type_attrs);
	kfree(tz->trip_temp_attrs);
	if (tz->ops->get_trip_hyst)
		kfree(tz->trip_hyst_attrs);
	kfree(tz->trips_attribute_group.attrs);
}