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
struct cpufreq_policy {int /*<<< orphan*/  related_cpus; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_show_cpus (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_related_cpus(struct cpufreq_policy *policy, char *buf)
{
	return cpufreq_show_cpus(policy->related_cpus, buf);
}