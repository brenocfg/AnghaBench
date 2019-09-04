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
struct wf_cpu_pid_state {int target; } ;
struct wf_control {int /*<<< orphan*/  name; } ;
typedef  int s32 ;
struct TYPE_2__ {int rmaxn_exhaust_fan; } ;

/* Variables and functions */
 int CPU_INTAKE_SCALE ; 
 int /*<<< orphan*/  DBG_LOTS (char*,...) ; 
 int /*<<< orphan*/  FAILURE_FAN ; 
 int /*<<< orphan*/  FAILURE_SENSOR ; 
 scalar_t__ cpu_check_overtemp (int) ; 
 struct wf_control** cpu_front_fans ; 
 int /*<<< orphan*/  cpu_max_all_fans () ; 
 TYPE_1__** cpu_mpu_data ; 
 struct wf_cpu_pid_state* cpu_pid ; 
 struct wf_control** cpu_pumps ; 
 struct wf_control** cpu_rear_fans ; 
 int /*<<< orphan*/  failure_state ; 
 int max (int,int) ; 
 int nr_chips ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 
 int read_one_cpu_vals (int,int*,int*) ; 
 int /*<<< orphan*/  wf_control_get (struct wf_control*,int*) ; 
 int wf_control_get_max (struct wf_control*) ; 
 int wf_control_set (struct wf_control*,int) ; 
 int /*<<< orphan*/  wf_cpu_pid_run (struct wf_cpu_pid_state*,int,int) ; 

__attribute__((used)) static void cpu_fans_tick_combined(void)
{
	s32 temp0, power0, temp1, power1, t_max = 0;
	s32 temp, power, intake, pump;
	struct wf_control *pump0, *pump1;
	struct wf_cpu_pid_state *sp = &cpu_pid[0];
	int err, cpu;

	DBG_LOTS("* cpu fans_tick_combined()\n");

	/* Read current speed from cpu 0 */
	wf_control_get(cpu_rear_fans[0], &sp->target);

	DBG_LOTS("  CPUs: cur_target = %d RPM\n", sp->target);

	/* Read values for both CPUs */
	err = read_one_cpu_vals(0, &temp0, &power0);
	if (err) {
		failure_state |= FAILURE_SENSOR;
		cpu_max_all_fans();
		return;
	}
	err = read_one_cpu_vals(1, &temp1, &power1);
	if (err) {
		failure_state |= FAILURE_SENSOR;
		cpu_max_all_fans();
		return;
	}

	/* Keep track of highest temp */
	t_max = max(t_max, max(temp0, temp1));

	/* Handle possible overtemps */
	if (cpu_check_overtemp(t_max))
		return;

	/* Use the max temp & power of both */
	temp = max(temp0, temp1);
	power = max(power0, power1);

	/* Run PID */
	wf_cpu_pid_run(sp, power, temp);

	/* Scale result for intake fan */
	intake = (sp->target * CPU_INTAKE_SCALE) >> 16;

	/* Same deal with pump speed */
	pump0 = cpu_pumps[0];
	pump1 = cpu_pumps[1];
	if (!pump0) {
		pump0 = pump1;
		pump1 = NULL;
	}
	pump = (sp->target * wf_control_get_max(pump0)) /
		cpu_mpu_data[0]->rmaxn_exhaust_fan;

	DBG_LOTS("  CPUs: target = %d RPM\n", sp->target);
	DBG_LOTS("  CPUs: intake = %d RPM\n", intake);
	DBG_LOTS("  CPUs: pump   = %d RPM\n", pump);

	for (cpu = 0; cpu < nr_chips; cpu++) {
		err = wf_control_set(cpu_rear_fans[cpu], sp->target);
		if (err) {
			pr_warning("wf_pm72: Fan %s reports error %d\n",
				   cpu_rear_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
		}
		err = wf_control_set(cpu_front_fans[cpu], intake);
		if (err) {
			pr_warning("wf_pm72: Fan %s reports error %d\n",
				   cpu_front_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
		}
		err = 0;
		if (cpu_pumps[cpu])
			err = wf_control_set(cpu_pumps[cpu], pump);
		if (err) {
			pr_warning("wf_pm72: Pump %s reports error %d\n",
				   cpu_pumps[cpu]->name, err);
			failure_state |= FAILURE_FAN;
		}
	}
}