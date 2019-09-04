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
struct policy_dbs_info {int work_in_progress; int /*<<< orphan*/  work_count; int /*<<< orphan*/  work; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  policy; } ;
struct cpufreq_policy {struct policy_dbs_info* governor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gov_clear_update_util (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_sync (int /*<<< orphan*/ *) ; 

void cpufreq_dbs_governor_stop(struct cpufreq_policy *policy)
{
	struct policy_dbs_info *policy_dbs = policy->governor_data;

	gov_clear_update_util(policy_dbs->policy);
	irq_work_sync(&policy_dbs->irq_work);
	cancel_work_sync(&policy_dbs->work);
	atomic_set(&policy_dbs->work_count, 0);
	policy_dbs->work_in_progress = false;
}