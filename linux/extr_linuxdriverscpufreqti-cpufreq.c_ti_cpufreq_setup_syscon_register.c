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
struct ti_cpufreq_data {int /*<<< orphan*/  syscon; struct device_node* opp_node; struct device* cpu_dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int ti_cpufreq_setup_syscon_register(struct ti_cpufreq_data *opp_data)
{
	struct device *dev = opp_data->cpu_dev;
	struct device_node *np = opp_data->opp_node;

	opp_data->syscon = syscon_regmap_lookup_by_phandle(np,
							"syscon");
	if (IS_ERR(opp_data->syscon)) {
		dev_err(dev,
			"\"syscon\" is missing, cannot use OPPv2 table.\n");
		return PTR_ERR(opp_data->syscon);
	}

	return 0;
}