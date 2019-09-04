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
typedef  int u64 ;
struct sched_param {int sched_priority; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SCHED_RR ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  exit_round_robin (unsigned int) ; 
 int idle_pct ; 
 int jiffies ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mark_tsc_unstable (char*) ; 
 int /*<<< orphan*/  mwait_idle_with_hints (int /*<<< orphan*/ ,int) ; 
 int need_resched () ; 
 int /*<<< orphan*/  power_saving_mwait_eax ; 
 int /*<<< orphan*/  round_robin_cpu (unsigned int) ; 
 int round_robin_time ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout_killable (int) ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 int /*<<< orphan*/  tick_broadcast_enable () ; 
 int /*<<< orphan*/  tick_broadcast_enter () ; 
 int /*<<< orphan*/  tick_broadcast_exit () ; 
 scalar_t__ time_before (unsigned long,int) ; 
 scalar_t__ tsc_detected_unstable ; 
 int tsc_marked_unstable ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int power_saving_thread(void *data)
{
	struct sched_param param = {.sched_priority = 1};
	int do_sleep;
	unsigned int tsk_index = (unsigned long)data;
	u64 last_jiffies = 0;

	sched_setscheduler(current, SCHED_RR, &param);

	while (!kthread_should_stop()) {
		unsigned long expire_time;

		/* round robin to cpus */
		expire_time = last_jiffies + round_robin_time * HZ;
		if (time_before(expire_time, jiffies)) {
			last_jiffies = jiffies;
			round_robin_cpu(tsk_index);
		}

		do_sleep = 0;

		expire_time = jiffies + HZ * (100 - idle_pct) / 100;

		while (!need_resched()) {
			if (tsc_detected_unstable && !tsc_marked_unstable) {
				/* TSC could halt in idle, so notify users */
				mark_tsc_unstable("TSC halts in idle");
				tsc_marked_unstable = 1;
			}
			local_irq_disable();
			tick_broadcast_enable();
			tick_broadcast_enter();
			stop_critical_timings();

			mwait_idle_with_hints(power_saving_mwait_eax, 1);

			start_critical_timings();
			tick_broadcast_exit();
			local_irq_enable();

			if (time_before(expire_time, jiffies)) {
				do_sleep = 1;
				break;
			}
		}

		/*
		 * current sched_rt has threshold for rt task running time.
		 * When a rt task uses 95% CPU time, the rt thread will be
		 * scheduled out for 5% CPU time to not starve other tasks. But
		 * the mechanism only works when all CPUs have RT task running,
		 * as if one CPU hasn't RT task, RT task from other CPUs will
		 * borrow CPU time from this CPU and cause RT task use > 95%
		 * CPU time. To make 'avoid starvation' work, takes a nap here.
		 */
		if (unlikely(do_sleep))
			schedule_timeout_killable(HZ * idle_pct / 100);

		/* If an external event has set the need_resched flag, then
		 * we need to deal with it, or this loop will continue to
		 * spin without calling __mwait().
		 */
		if (unlikely(need_resched()))
			schedule();
	}

	exit_round_robin(tsk_index);
	return 0;
}