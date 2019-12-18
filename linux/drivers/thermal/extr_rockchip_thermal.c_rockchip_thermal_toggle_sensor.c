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
struct thermal_zone_device {TYPE_1__* ops; } ;
struct rockchip_thermal_sensor {struct thermal_zone_device* tzd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mode ) (struct thermal_zone_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  THERMAL_DEVICE_DISABLED ; 
 int /*<<< orphan*/  THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  stub1 (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rockchip_thermal_toggle_sensor(struct rockchip_thermal_sensor *sensor, bool on)
{
	struct thermal_zone_device *tzd = sensor->tzd;

	tzd->ops->set_mode(tzd,
		on ? THERMAL_DEVICE_ENABLED : THERMAL_DEVICE_DISABLED);
}