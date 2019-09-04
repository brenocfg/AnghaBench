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
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpufreq_clamp ; 
 scalar_t__ fan_cpu_main ; 
 scalar_t__ fan_hd ; 
 scalar_t__ fan_system ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ sensor_cpu_power ; 
 scalar_t__ sensor_cpu_temp ; 
 scalar_t__ sensor_hd_temp ; 
 int /*<<< orphan*/  wf_put_control (scalar_t__) ; 
 int /*<<< orphan*/  wf_put_sensor (scalar_t__) ; 
 int /*<<< orphan*/  wf_smu_cpu_fans ; 
 int /*<<< orphan*/  wf_smu_events ; 
 int /*<<< orphan*/  wf_smu_sys_fans ; 
 int /*<<< orphan*/  wf_unregister_client (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wf_smu_remove(struct platform_device *ddev)
{
	wf_unregister_client(&wf_smu_events);

	/* XXX We don't have yet a guarantee that our callback isn't
	 * in progress when returning from wf_unregister_client, so
	 * we add an arbitrary delay. I'll have to fix that in the core
	 */
	msleep(1000);

	/* Release all sensors */
	/* One more crappy race: I don't think we have any guarantee here
	 * that the attribute callback won't race with the sensor beeing
	 * disposed of, and I'm not 100% certain what best way to deal
	 * with that except by adding locks all over... I'll do that
	 * eventually but heh, who ever rmmod this module anyway ?
	 */
	if (sensor_cpu_power)
		wf_put_sensor(sensor_cpu_power);
	if (sensor_cpu_temp)
		wf_put_sensor(sensor_cpu_temp);
	if (sensor_hd_temp)
		wf_put_sensor(sensor_hd_temp);

	/* Release all controls */
	if (fan_cpu_main)
		wf_put_control(fan_cpu_main);
	if (fan_hd)
		wf_put_control(fan_hd);
	if (fan_system)
		wf_put_control(fan_system);
	if (cpufreq_clamp)
		wf_put_control(cpufreq_clamp);

	/* Destroy control loops state structures */
	kfree(wf_smu_sys_fans);
	kfree(wf_smu_cpu_fans);

	return 0;
}