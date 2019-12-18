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
struct thermal_zone_device {int trips; } ;
struct thermal_cooling_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_max_state ) (struct thermal_cooling_device*,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct thermal_cooling_device*,unsigned long*) ; 

__attribute__((used)) static long get_target_state(struct thermal_zone_device *tz,
		struct thermal_cooling_device *cdev, int percentage, int level)
{
	unsigned long max_state;

	cdev->ops->get_max_state(cdev, &max_state);

	return (long)(percentage * level * max_state) / (100 * tz->trips);
}