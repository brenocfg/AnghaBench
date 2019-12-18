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
struct thermal_zone_device {struct __thermal_zone* devdata; } ;
struct __thermal_zone {int ntrips; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct __thermal_zone*) ; 

int of_thermal_get_ntrips(struct thermal_zone_device *tz)
{
	struct __thermal_zone *data = tz->devdata;

	if (!data || IS_ERR(data))
		return -ENODEV;

	return data->ntrips;
}