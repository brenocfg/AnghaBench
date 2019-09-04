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
struct cpufreq_policy {int /*<<< orphan*/ * governor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userspace_mutex ; 

__attribute__((used)) static void cpufreq_userspace_policy_exit(struct cpufreq_policy *policy)
{
	mutex_lock(&userspace_mutex);
	kfree(policy->governor_data);
	policy->governor_data = NULL;
	mutex_unlock(&userspace_mutex);
}