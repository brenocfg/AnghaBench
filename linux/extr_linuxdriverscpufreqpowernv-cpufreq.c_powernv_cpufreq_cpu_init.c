#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kernfs_node {int dummy; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct global_pstate_info {int /*<<< orphan*/  gpstate_lock; TYPE_1__ timer; struct cpufreq_policy* policy; } ;
struct TYPE_7__ {int /*<<< orphan*/  sd; } ;
struct cpufreq_policy {int fast_switch_possible; struct global_pstate_info* driver_data; int /*<<< orphan*/  freq_table; int /*<<< orphan*/  cpu; TYPE_3__ kobj; int /*<<< orphan*/  cpus; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPSTATE_TIMER_INTERVAL ; 
 int /*<<< orphan*/  PVR_POWER9 ; 
 int TIMER_DEFERRABLE ; 
 int TIMER_PINNED ; 
 int cpu_first_thread_sibling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpstate_timer_handler ; 
 scalar_t__ jiffies ; 
 struct kernfs_node* kernfs_find_and_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 struct global_pstate_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernv_freqs ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pvr_version_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (TYPE_3__*,TYPE_2__*) ; 
 int threads_per_core ; 
 TYPE_2__ throttle_attr_grp ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int powernv_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	int base, i;
	struct kernfs_node *kn;
	struct global_pstate_info *gpstates;

	base = cpu_first_thread_sibling(policy->cpu);

	for (i = 0; i < threads_per_core; i++)
		cpumask_set_cpu(base + i, policy->cpus);

	kn = kernfs_find_and_get(policy->kobj.sd, throttle_attr_grp.name);
	if (!kn) {
		int ret;

		ret = sysfs_create_group(&policy->kobj, &throttle_attr_grp);
		if (ret) {
			pr_info("Failed to create throttle stats directory for cpu %d\n",
				policy->cpu);
			return ret;
		}
	} else {
		kernfs_put(kn);
	}

	policy->freq_table = powernv_freqs;
	policy->fast_switch_possible = true;

	if (pvr_version_is(PVR_POWER9))
		return 0;

	/* Initialise Gpstate ramp-down timer only on POWER8 */
	gpstates =  kzalloc(sizeof(*gpstates), GFP_KERNEL);
	if (!gpstates)
		return -ENOMEM;

	policy->driver_data = gpstates;

	/* initialize timer */
	gpstates->policy = policy;
	timer_setup(&gpstates->timer, gpstate_timer_handler,
		    TIMER_PINNED | TIMER_DEFERRABLE);
	gpstates->timer.expires = jiffies +
				msecs_to_jiffies(GPSTATE_TIMER_INTERVAL);
	spin_lock_init(&gpstates->gpstate_lock);

	return 0;
}