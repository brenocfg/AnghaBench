#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wf_cpu_pid_state {int target; } ;
typedef  int s32 ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CPU_INTAKE_SCALE ; 
 int /*<<< orphan*/  DBG_LOTS (char*,...) ; 
 int /*<<< orphan*/  FAILURE_FAN ; 
 int /*<<< orphan*/  FAILURE_SENSOR ; 
 scalar_t__ cpu_check_overtemp (int) ; 
 TYPE_1__** cpu_front_fans ; 
 int /*<<< orphan*/  cpu_max_all_fans () ; 
 struct wf_cpu_pid_state* cpu_pid ; 
 TYPE_1__** cpu_rear_fans ; 
 int /*<<< orphan*/  failure_state ; 
 int max (int,int) ; 
 int nr_chips ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 
 int read_one_cpu_vals (int,int*,int*) ; 
 int /*<<< orphan*/  wf_control_get (TYPE_1__*,int*) ; 
 int wf_control_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wf_cpu_pid_run (struct wf_cpu_pid_state*,int,int) ; 

__attribute__((used)) static void cpu_fans_tick_split(void)
{
	int err, cpu;
	s32 intake, temp, power, t_max = 0;

	DBG_LOTS("* cpu fans_tick_split()\n");

	for (cpu = 0; cpu < nr_chips; ++cpu) {
		struct wf_cpu_pid_state *sp = &cpu_pid[cpu];

		/* Read current speed */
		wf_control_get(cpu_rear_fans[cpu], &sp->target);

		DBG_LOTS("  CPU%d: cur_target = %d RPM\n", cpu, sp->target);

		err = read_one_cpu_vals(cpu, &temp, &power);
		if (err) {
			failure_state |= FAILURE_SENSOR;
			cpu_max_all_fans();
			return;
		}

		/* Keep track of highest temp */
		t_max = max(t_max, temp);

		/* Handle possible overtemps */
		if (cpu_check_overtemp(t_max))
			return;

		/* Run PID */
		wf_cpu_pid_run(sp, power, temp);

		DBG_LOTS("  CPU%d: target = %d RPM\n", cpu, sp->target);

		/* Apply result directly to exhaust fan */
		err = wf_control_set(cpu_rear_fans[cpu], sp->target);
		if (err) {
			pr_warning("wf_pm72: Fan %s reports error %d\n",
			       cpu_rear_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
			break;
		}

		/* Scale result for intake fan */
		intake = (sp->target * CPU_INTAKE_SCALE) >> 16;
		DBG_LOTS("  CPU%d: intake = %d RPM\n", cpu, intake);
		err = wf_control_set(cpu_front_fans[cpu], intake);
		if (err) {
			pr_warning("wf_pm72: Fan %s reports error %d\n",
			       cpu_front_fans[cpu]->name, err);
			failure_state |= FAILURE_FAN;
			break;
		}
	}
}