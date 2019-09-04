#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wf_cpu_pid_state {int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOTS (char*,...) ; 
 int /*<<< orphan*/  FAILURE_FAN ; 
 int /*<<< orphan*/  FAILURE_SENSOR ; 
 scalar_t__ cpu_check_overtemp (int /*<<< orphan*/ ) ; 
 TYPE_1__*** cpu_fans ; 
 int /*<<< orphan*/  cpu_max_all_fans () ; 
 struct wf_cpu_pid_state* cpu_pid ; 
 int /*<<< orphan*/  dimms_output_clamp ; 
 int /*<<< orphan*/  failure_state ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_chips ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 
 int read_one_cpu_vals (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wf_control_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int wf_control_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_cpu_pid_run (struct wf_cpu_pid_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_fans_tick(void)
{
	int err, cpu, i;
	s32 speed, temp, power, t_max = 0;

	DBG_LOTS("* cpu fans_tick_split()\n");

	for (cpu = 0; cpu < nr_chips; ++cpu) {
		struct wf_cpu_pid_state *sp = &cpu_pid[cpu];

		/* Read current speed */
		wf_control_get(cpu_fans[cpu][0], &sp->target);

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

		/* Apply DIMMs clamp */
		speed = max(sp->target, dimms_output_clamp);

		/* Apply result to all cpu fans */
		for (i = 0; i < 3; i++) {
			err = wf_control_set(cpu_fans[cpu][i], speed);
			if (err) {
				pr_warning("wf_rm31: Fan %s reports error %d\n",
					   cpu_fans[cpu][i]->name, err);
				failure_state |= FAILURE_FAN;
			}
		}
	}
}