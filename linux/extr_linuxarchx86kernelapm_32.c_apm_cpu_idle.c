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
typedef  scalar_t__ u64 ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ forbid_idle; } ;

/* Variables and functions */
 unsigned int IDLE_CALC_LIMIT ; 
 unsigned int IDLE_LEAKY_MAX ; 
 int /*<<< orphan*/  apm_do_busy () ; 
 int apm_do_idle () ; 
 TYPE_1__ apm_info ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  default_idle () ; 
 unsigned int idle_period ; 
 unsigned int idle_threshold ; 
 unsigned int jiffies ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  need_resched () ; 
 unsigned int nsecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  task_cputime (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int apm_cpu_idle(struct cpuidle_device *dev,
	struct cpuidle_driver *drv, int index)
{
	static int use_apm_idle; /* = 0 */
	static unsigned int last_jiffies; /* = 0 */
	static u64 last_stime; /* = 0 */
	u64 stime, utime;

	int apm_idle_done = 0;
	unsigned int jiffies_since_last_check = jiffies - last_jiffies;
	unsigned int bucket;

recalc:
	task_cputime(current, &utime, &stime);
	if (jiffies_since_last_check > IDLE_CALC_LIMIT) {
		use_apm_idle = 0;
	} else if (jiffies_since_last_check > idle_period) {
		unsigned int idle_percentage;

		idle_percentage = nsecs_to_jiffies(stime - last_stime);
		idle_percentage *= 100;
		idle_percentage /= jiffies_since_last_check;
		use_apm_idle = (idle_percentage > idle_threshold);
		if (apm_info.forbid_idle)
			use_apm_idle = 0;
	}

	last_jiffies = jiffies;
	last_stime = stime;

	bucket = IDLE_LEAKY_MAX;

	while (!need_resched()) {
		if (use_apm_idle) {
			unsigned int t;

			t = jiffies;
			switch (apm_do_idle()) {
			case 0:
				apm_idle_done = 1;
				if (t != jiffies) {
					if (bucket) {
						bucket = IDLE_LEAKY_MAX;
						continue;
					}
				} else if (bucket) {
					bucket--;
					continue;
				}
				break;
			case 1:
				apm_idle_done = 1;
				break;
			default: /* BIOS refused */
				break;
			}
		}
		default_idle();
		local_irq_disable();
		jiffies_since_last_check = jiffies - last_jiffies;
		if (jiffies_since_last_check > idle_period)
			goto recalc;
	}

	if (apm_idle_done)
		apm_do_busy();

	return index;
}