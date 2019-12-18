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
struct thermal_zone_device {struct adapter* devdata; } ;
struct TYPE_2__ {int trip_temp; } ;
struct adapter {TYPE_1__ ch_thermal; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int cxgb4_thermal_get_trip_temp(struct thermal_zone_device *tzdev,
				       int trip, int *temp)
{
	struct adapter *adap = tzdev->devdata;

	if (!adap->ch_thermal.trip_temp)
		return -EINVAL;

	*temp = adap->ch_thermal.trip_temp;
	return 0;
}