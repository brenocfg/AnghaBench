#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_3__ ddata ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 TYPE_1__* get_cpu_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  platform_device_register_simple (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sti_cpufreq_fetch_syscon_registers () ; 
 int sti_cpufreq_set_opp_info () ; 

__attribute__((used)) static int sti_cpufreq_init(void)
{
	int ret;

	if ((!of_machine_is_compatible("st,stih407")) &&
		(!of_machine_is_compatible("st,stih410")))
		return -ENODEV;

	ddata.cpu = get_cpu_device(0);
	if (!ddata.cpu) {
		dev_err(ddata.cpu, "Failed to get device for CPU0\n");
		goto skip_voltage_scaling;
	}

	if (!of_get_property(ddata.cpu->of_node, "operating-points-v2", NULL)) {
		dev_err(ddata.cpu, "OPP-v2 not supported\n");
		goto skip_voltage_scaling;
	}

	ret = sti_cpufreq_fetch_syscon_registers();
	if (ret)
		goto skip_voltage_scaling;

	ret = sti_cpufreq_set_opp_info();
	if (!ret)
		goto register_cpufreq_dt;

skip_voltage_scaling:
	dev_err(ddata.cpu, "Not doing voltage scaling\n");

register_cpufreq_dt:
	platform_device_register_simple("cpufreq-dt", -1, NULL, 0);

	return 0;
}