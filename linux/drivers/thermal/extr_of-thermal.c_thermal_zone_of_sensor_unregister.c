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
struct thermal_zone_device {int /*<<< orphan*/  lock; TYPE_1__* ops; struct __thermal_zone* devdata; } ;
struct device {int dummy; } ;
struct __thermal_zone {int /*<<< orphan*/ * sensor_data; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {int /*<<< orphan*/ * set_emul_temp; int /*<<< orphan*/ * get_trend; int /*<<< orphan*/ * get_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void thermal_zone_of_sensor_unregister(struct device *dev,
				       struct thermal_zone_device *tzd)
{
	struct __thermal_zone *tz;

	if (!dev || !tzd || !tzd->devdata)
		return;

	tz = tzd->devdata;

	/* no __thermal_zone, nothing to be done */
	if (!tz)
		return;

	mutex_lock(&tzd->lock);
	tzd->ops->get_temp = NULL;
	tzd->ops->get_trend = NULL;
	tzd->ops->set_emul_temp = NULL;

	tz->ops = NULL;
	tz->sensor_data = NULL;
	mutex_unlock(&tzd->lock);
}