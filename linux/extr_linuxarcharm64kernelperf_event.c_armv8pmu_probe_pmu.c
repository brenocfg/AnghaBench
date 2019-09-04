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
struct armv8pmu_probe_info {int present; struct arm_pmu* pmu; } ;
struct arm_pmu {int /*<<< orphan*/  supported_cpus; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  __armv8pmu_probe_pmu ; 
 int smp_call_function_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct armv8pmu_probe_info*,int) ; 

__attribute__((used)) static int armv8pmu_probe_pmu(struct arm_pmu *cpu_pmu)
{
	struct armv8pmu_probe_info probe = {
		.pmu = cpu_pmu,
		.present = false,
	};
	int ret;

	ret = smp_call_function_any(&cpu_pmu->supported_cpus,
				    __armv8pmu_probe_pmu,
				    &probe, 1);
	if (ret)
		return ret;

	return probe.present ? 0 : -ENODEV;
}