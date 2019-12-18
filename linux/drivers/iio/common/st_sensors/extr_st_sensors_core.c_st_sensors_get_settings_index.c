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
struct st_sensor_settings {int /*<<< orphan*/ * sensors_supported; } ;

/* Variables and functions */
 int ENODEV ; 
 int ST_SENSORS_MAX_4WAI ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int st_sensors_get_settings_index(const char *name,
				  const struct st_sensor_settings *list,
				  const int list_length)
{
	int i, n;

	for (i = 0; i < list_length; i++) {
		for (n = 0; n < ST_SENSORS_MAX_4WAI; n++) {
			if (strcmp(name, list[i].sensors_supported[n]) == 0)
				return i;
		}
	}

	return -ENODEV;
}