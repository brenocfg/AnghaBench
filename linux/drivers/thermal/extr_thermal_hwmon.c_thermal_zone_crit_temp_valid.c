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
struct TYPE_2__ {int /*<<< orphan*/  (* get_crit_temp ) (struct thermal_zone_device*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct thermal_zone_device*,int*) ; 

__attribute__((used)) static bool thermal_zone_crit_temp_valid(struct thermal_zone_device *tz)
{
	int temp;
	return tz->ops->get_crit_temp && !tz->ops->get_crit_temp(tz, &temp);
}