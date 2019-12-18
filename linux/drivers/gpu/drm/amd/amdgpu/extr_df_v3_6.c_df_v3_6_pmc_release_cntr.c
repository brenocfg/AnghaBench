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
typedef  int /*<<< orphan*/  uint64_t ;
struct amdgpu_device {unsigned long long* df_perfmon_config_assign_mask; } ;

/* Variables and functions */
 int df_v3_6_pmc_config_2_cntr (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void df_v3_6_pmc_release_cntr(struct amdgpu_device *adev,
				     uint64_t config)
{
	int target_cntr = df_v3_6_pmc_config_2_cntr(adev, config);

	if (target_cntr >= 0)
		adev->df_perfmon_config_assign_mask[target_cntr] = 0ULL;
}