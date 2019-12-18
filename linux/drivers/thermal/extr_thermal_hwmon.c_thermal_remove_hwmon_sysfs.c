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
struct thermal_zone_device {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
struct thermal_hwmon_temp {int /*<<< orphan*/  device; int /*<<< orphan*/  node; int /*<<< orphan*/  tz_list; int /*<<< orphan*/  hwmon_node; TYPE_2__ temp_crit; TYPE_1__ temp_input; } ;
struct thermal_hwmon_device {int /*<<< orphan*/  device; int /*<<< orphan*/  node; int /*<<< orphan*/  tz_list; int /*<<< orphan*/  hwmon_node; TYPE_2__ temp_crit; TYPE_1__ temp_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct thermal_hwmon_temp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_hwmon_list_lock ; 
 struct thermal_hwmon_temp* thermal_hwmon_lookup_by_type (struct thermal_zone_device*) ; 
 struct thermal_hwmon_temp* thermal_hwmon_lookup_temp (struct thermal_hwmon_temp*,struct thermal_zone_device*) ; 
 scalar_t__ thermal_zone_crit_temp_valid (struct thermal_zone_device*) ; 
 scalar_t__ unlikely (int) ; 

void thermal_remove_hwmon_sysfs(struct thermal_zone_device *tz)
{
	struct thermal_hwmon_device *hwmon;
	struct thermal_hwmon_temp *temp;

	hwmon = thermal_hwmon_lookup_by_type(tz);
	if (unlikely(!hwmon)) {
		/* Should never happen... */
		dev_dbg(&tz->device, "hwmon device lookup failed!\n");
		return;
	}

	temp = thermal_hwmon_lookup_temp(hwmon, tz);
	if (unlikely(!temp)) {
		/* Should never happen... */
		dev_dbg(&tz->device, "temperature input lookup failed!\n");
		return;
	}

	device_remove_file(hwmon->device, &temp->temp_input.attr);
	if (thermal_zone_crit_temp_valid(tz))
		device_remove_file(hwmon->device, &temp->temp_crit.attr);

	mutex_lock(&thermal_hwmon_list_lock);
	list_del(&temp->hwmon_node);
	kfree(temp);
	if (!list_empty(&hwmon->tz_list)) {
		mutex_unlock(&thermal_hwmon_list_lock);
		return;
	}
	list_del(&hwmon->node);
	mutex_unlock(&thermal_hwmon_list_lock);

	hwmon_device_unregister(hwmon->device);
	kfree(hwmon);
}