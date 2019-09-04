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
struct freq_attr {int /*<<< orphan*/  (* show ) (struct cpufreq_policy*,char*) ;} ;
struct cpufreq_policy {int /*<<< orphan*/  rwsem; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cpufreq_policy*,char*) ; 
 struct freq_attr* to_attr (struct attribute*) ; 
 struct cpufreq_policy* to_policy (struct kobject*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	struct cpufreq_policy *policy = to_policy(kobj);
	struct freq_attr *fattr = to_attr(attr);
	ssize_t ret;

	down_read(&policy->rwsem);
	ret = fattr->show(policy, buf);
	up_read(&policy->rwsem);

	return ret;
}