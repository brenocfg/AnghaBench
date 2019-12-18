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
struct thermal_zone_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  passive_delay; int /*<<< orphan*/  polling_delay; struct __thermal_zone* devdata; } ;
struct __thermal_zone {int mode; int /*<<< orphan*/  passive_delay; int /*<<< orphan*/  polling_delay; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */
 int THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_update (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_thermal_set_mode(struct thermal_zone_device *tz,
			       enum thermal_device_mode mode)
{
	struct __thermal_zone *data = tz->devdata;

	mutex_lock(&tz->lock);

	if (mode == THERMAL_DEVICE_ENABLED) {
		tz->polling_delay = data->polling_delay;
		tz->passive_delay = data->passive_delay;
	} else {
		tz->polling_delay = 0;
		tz->passive_delay = 0;
	}

	mutex_unlock(&tz->lock);

	data->mode = mode;
	thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	return 0;
}