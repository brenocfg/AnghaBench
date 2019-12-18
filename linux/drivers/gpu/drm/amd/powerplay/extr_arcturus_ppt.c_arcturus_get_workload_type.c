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
struct smu_context {int dummy; } ;
struct smu_11_0_cmn2aisc_mapping {int map_to; int /*<<< orphan*/  valid_mapping; } ;
typedef  enum PP_SMC_POWER_PROFILE { ____Placeholder_PP_SMC_POWER_PROFILE } PP_SMC_POWER_PROFILE ;

/* Variables and functions */
 int EINVAL ; 
 int PP_SMC_POWER_PROFILE_CUSTOM ; 
 struct smu_11_0_cmn2aisc_mapping* arcturus_workload_map ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int arcturus_get_workload_type(struct smu_context *smu, enum PP_SMC_POWER_PROFILE profile)
{
	struct smu_11_0_cmn2aisc_mapping mapping;

	if (profile > PP_SMC_POWER_PROFILE_CUSTOM)
		return -EINVAL;

	mapping = arcturus_workload_map[profile];
	if (!(mapping.valid_mapping)) {
		pr_warn("Unsupported SMU power source: %d\n", profile);
		return -EINVAL;
	}

	return mapping.map_to;
}