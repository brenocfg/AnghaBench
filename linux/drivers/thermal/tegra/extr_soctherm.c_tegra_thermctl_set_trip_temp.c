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
struct thermal_zone_device {TYPE_1__* ops; } ;
struct thermal_cooling_device {int /*<<< orphan*/  type; } ;
struct tegra_tsensor_group {int /*<<< orphan*/  id; } ;
struct tegra_thermctl_zone {struct device* dev; struct tegra_tsensor_group* sg; struct tegra_soctherm* ts; struct thermal_zone_device* tz; } ;
struct tegra_soctherm {TYPE_2__* throt_cfgs; } ;
struct soctherm_throt_cfg {int dummy; } ;
struct device {int dummy; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_4__ {struct thermal_cooling_device* cdev; int /*<<< orphan*/  init; } ;
struct TYPE_3__ {int (* get_trip_type ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int THERMAL_TRIP_CRITICAL ; 
 int THERMAL_TRIP_HOT ; 
 int THROTTLE_SIZE ; 
 struct soctherm_throt_cfg* find_throttle_cfg_by_name (struct tegra_soctherm*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_thermal_instance (struct thermal_zone_device*,struct thermal_cooling_device*,int) ; 
 scalar_t__ min_low_temp ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 
 int thermtrip_program (struct device*,struct tegra_tsensor_group const*,int) ; 
 int throttrip_program (struct device*,struct tegra_tsensor_group const*,struct soctherm_throt_cfg*,int) ; 
 scalar_t__ tsensor_group_thermtrip_get (struct tegra_soctherm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_thermctl_set_trip_temp(void *data, int trip, int temp)
{
	struct tegra_thermctl_zone *zone = data;
	struct thermal_zone_device *tz = zone->tz;
	struct tegra_soctherm *ts = zone->ts;
	const struct tegra_tsensor_group *sg = zone->sg;
	struct device *dev = zone->dev;
	enum thermal_trip_type type;
	int ret;

	if (!tz)
		return -EINVAL;

	ret = tz->ops->get_trip_type(tz, trip, &type);
	if (ret)
		return ret;

	if (type == THERMAL_TRIP_CRITICAL) {
		/*
		 * If thermtrips property is set in DT,
		 * doesn't need to program critical type trip to HW,
		 * if not, program critical trip to HW.
		 */
		if (min_low_temp == tsensor_group_thermtrip_get(ts, sg->id))
			return thermtrip_program(dev, sg, temp);
		else
			return 0;

	} else if (type == THERMAL_TRIP_HOT) {
		int i;

		for (i = 0; i < THROTTLE_SIZE; i++) {
			struct thermal_cooling_device *cdev;
			struct soctherm_throt_cfg *stc;

			if (!ts->throt_cfgs[i].init)
				continue;

			cdev = ts->throt_cfgs[i].cdev;
			if (get_thermal_instance(tz, cdev, trip))
				stc = find_throttle_cfg_by_name(ts, cdev->type);
			else
				continue;

			return throttrip_program(dev, sg, stc, temp);
		}
	}

	return 0;
}