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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {void* syscfg_eng; void* syscfg; struct device* cpu; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 TYPE_1__ ddata ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int sti_cpufreq_fetch_syscon_registers(void)
{
	struct device *dev = ddata.cpu;
	struct device_node *np = dev->of_node;

	ddata.syscfg = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	if (IS_ERR(ddata.syscfg)) {
		dev_err(dev,  "\"st,syscfg\" not supplied\n");
		return PTR_ERR(ddata.syscfg);
	}

	ddata.syscfg_eng = syscon_regmap_lookup_by_phandle(np, "st,syscfg-eng");
	if (IS_ERR(ddata.syscfg_eng)) {
		dev_err(dev, "\"st,syscfg-eng\" not supplied\n");
		return PTR_ERR(ddata.syscfg_eng);
	}

	return 0;
}