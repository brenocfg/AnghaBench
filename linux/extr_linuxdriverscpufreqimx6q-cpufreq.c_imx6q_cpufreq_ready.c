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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev ; 
 int /*<<< orphan*/  cpu_dev ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_cpufreq_cooling_register (struct cpufreq_policy*) ; 

__attribute__((used)) static void imx6q_cpufreq_ready(struct cpufreq_policy *policy)
{
	cdev = of_cpufreq_cooling_register(policy);

	if (!cdev)
		dev_err(cpu_dev,
			"running cpufreq without cooling device: %ld\n",
			PTR_ERR(cdev));
}