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
typedef  int /*<<< orphan*/  u32 ;
struct thermal_cooling_device {int dummy; } ;
struct device_node {int dummy; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct thermal_cooling_device*) ; 
 int /*<<< orphan*/  PTR_ERR (struct thermal_cooling_device*) ; 
 struct thermal_cooling_device* __cpufreq_cooling_register (struct device_node*,struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_cpu_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

struct thermal_cooling_device *
of_cpufreq_cooling_register(struct cpufreq_policy *policy)
{
	struct device_node *np = of_get_cpu_node(policy->cpu, NULL);
	struct thermal_cooling_device *cdev = NULL;
	u32 capacitance = 0;

	if (!np) {
		pr_err("cpu_cooling: OF node not available for cpu%d\n",
		       policy->cpu);
		return NULL;
	}

	if (of_find_property(np, "#cooling-cells", NULL)) {
		of_property_read_u32(np, "dynamic-power-coefficient",
				     &capacitance);

		cdev = __cpufreq_cooling_register(np, policy, capacitance);
		if (IS_ERR(cdev)) {
			pr_err("cpu_cooling: cpu%d failed to register as cooling device: %ld\n",
			       policy->cpu, PTR_ERR(cdev));
			cdev = NULL;
		}
	}

	of_node_put(np);
	return cdev;
}