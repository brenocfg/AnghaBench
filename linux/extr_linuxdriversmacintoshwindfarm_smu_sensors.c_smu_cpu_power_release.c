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
struct wf_sensor {int dummy; } ;
struct smu_cpu_power_sensor {scalar_t__ amps; scalar_t__ volts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smu_cpu_power_sensor*) ; 
 struct smu_cpu_power_sensor* to_smu_cpu_power (struct wf_sensor*) ; 
 int /*<<< orphan*/  wf_put_sensor (scalar_t__) ; 

__attribute__((used)) static void smu_cpu_power_release(struct wf_sensor *sr)
{
	struct smu_cpu_power_sensor *pow = to_smu_cpu_power(sr);

	if (pow->volts)
		wf_put_sensor(pow->volts);
	if (pow->amps)
		wf_put_sensor(pow->amps);
	kfree(pow);
}