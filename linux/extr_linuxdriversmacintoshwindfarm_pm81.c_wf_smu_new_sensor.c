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
struct wf_sensor {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct wf_sensor* sensor_cpu_power ; 
 struct wf_sensor* sensor_cpu_temp ; 
 struct wf_sensor* sensor_hd_temp ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wf_get_sensor (struct wf_sensor*) ; 
 int wf_smu_all_sensors_ok ; 

__attribute__((used)) static void wf_smu_new_sensor(struct wf_sensor *sr)
{
	if (wf_smu_all_sensors_ok)
		return;

	if (sensor_cpu_power == NULL && !strcmp(sr->name, "cpu-power")) {
		if (wf_get_sensor(sr) == 0)
			sensor_cpu_power = sr;
	}

	if (sensor_cpu_temp == NULL && !strcmp(sr->name, "cpu-temp")) {
		if (wf_get_sensor(sr) == 0)
			sensor_cpu_temp = sr;
	}

	if (sensor_hd_temp == NULL && !strcmp(sr->name, "hd-temp")) {
		if (wf_get_sensor(sr) == 0)
			sensor_hd_temp = sr;
	}

	if (sensor_cpu_power && sensor_cpu_temp && sensor_hd_temp)
		wf_smu_all_sensors_ok = 1;
}