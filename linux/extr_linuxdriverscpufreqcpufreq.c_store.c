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
struct freq_attr {int /*<<< orphan*/  (* store ) (struct cpufreq_policy*,char const*,size_t) ;} ;
struct cpufreq_policy {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  cpu; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ cpu_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_read_trylock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cpufreq_policy*,char const*,size_t) ; 
 struct freq_attr* to_attr (struct attribute*) ; 
 struct cpufreq_policy* to_policy (struct kobject*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store(struct kobject *kobj, struct attribute *attr,
		     const char *buf, size_t count)
{
	struct cpufreq_policy *policy = to_policy(kobj);
	struct freq_attr *fattr = to_attr(attr);
	ssize_t ret = -EINVAL;

	/*
	 * cpus_read_trylock() is used here to work around a circular lock
	 * dependency problem with respect to the cpufreq_register_driver().
	 */
	if (!cpus_read_trylock())
		return -EBUSY;

	if (cpu_online(policy->cpu)) {
		down_write(&policy->rwsem);
		ret = fattr->store(policy, buf, count);
		up_write(&policy->rwsem);
	}

	cpus_read_unlock();

	return ret;
}