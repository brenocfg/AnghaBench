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
struct kobject {int dummy; } ;
struct completion {int dummy; } ;
struct cpufreq_policy {int /*<<< orphan*/  rwsem; struct completion kobj_unregister; struct kobject kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_stats_free_table (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static void cpufreq_policy_put_kobj(struct cpufreq_policy *policy)
{
	struct kobject *kobj;
	struct completion *cmp;

	down_write(&policy->rwsem);
	cpufreq_stats_free_table(policy);
	kobj = &policy->kobj;
	cmp = &policy->kobj_unregister;
	up_write(&policy->rwsem);
	kobject_put(kobj);

	/*
	 * We need to make sure that the underlying kobj is
	 * actually not referenced anymore by anybody before we
	 * proceed with unloading.
	 */
	pr_debug("waiting for dropping of refcount\n");
	wait_for_completion(cmp);
	pr_debug("wait complete\n");
}