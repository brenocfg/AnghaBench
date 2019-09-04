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
struct cpufreq_policy {struct cpufreq_governor* governor; int /*<<< orphan*/  policy; } ;
struct cpufreq_governor {int /*<<< orphan*/  owner; } ;
struct TYPE_2__ {scalar_t__ setpolicy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_NAME_LEN ; 
 int /*<<< orphan*/  CPUFREQ_POLICY_PERFORMANCE ; 
 int /*<<< orphan*/  CPUFREQ_POLICY_POWERSAVE ; 
 int EINVAL ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_governor_mutex ; 
 struct cpufreq_governor* find_governor (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_module (char*,char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_parse_governor(char *str_governor,
				  struct cpufreq_policy *policy)
{
	if (cpufreq_driver->setpolicy) {
		if (!strncasecmp(str_governor, "performance", CPUFREQ_NAME_LEN)) {
			policy->policy = CPUFREQ_POLICY_PERFORMANCE;
			return 0;
		}

		if (!strncasecmp(str_governor, "powersave", CPUFREQ_NAME_LEN)) {
			policy->policy = CPUFREQ_POLICY_POWERSAVE;
			return 0;
		}
	} else {
		struct cpufreq_governor *t;

		mutex_lock(&cpufreq_governor_mutex);

		t = find_governor(str_governor);
		if (!t) {
			int ret;

			mutex_unlock(&cpufreq_governor_mutex);

			ret = request_module("cpufreq_%s", str_governor);
			if (ret)
				return -EINVAL;

			mutex_lock(&cpufreq_governor_mutex);

			t = find_governor(str_governor);
		}
		if (t && !try_module_get(t->owner))
			t = NULL;

		mutex_unlock(&cpufreq_governor_mutex);

		if (t) {
			policy->governor = t;
			return 0;
		}
	}

	return -EINVAL;
}