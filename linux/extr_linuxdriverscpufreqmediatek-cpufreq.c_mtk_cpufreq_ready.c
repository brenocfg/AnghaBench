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
struct mtk_cpu_dvfs_info {int /*<<< orphan*/  cdev; } ;
struct cpufreq_policy {struct mtk_cpu_dvfs_info* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_cpufreq_cooling_register (struct cpufreq_policy*) ; 

__attribute__((used)) static void mtk_cpufreq_ready(struct cpufreq_policy *policy)
{
	struct mtk_cpu_dvfs_info *info = policy->driver_data;

	info->cdev = of_cpufreq_cooling_register(policy);
}