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
struct st_sensor_settings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct st_sensor_settings const*) ; 
 struct st_sensor_settings const* st_gyro_sensors_settings ; 
 int st_sensors_get_settings_index (char const*,struct st_sensor_settings const*,int /*<<< orphan*/ ) ; 

const struct st_sensor_settings *st_gyro_get_settings(const char *name)
{
	int index = st_sensors_get_settings_index(name,
					st_gyro_sensors_settings,
					ARRAY_SIZE(st_gyro_sensors_settings));
	if (index < 0)
		return NULL;

	return &st_gyro_sensors_settings[index];
}