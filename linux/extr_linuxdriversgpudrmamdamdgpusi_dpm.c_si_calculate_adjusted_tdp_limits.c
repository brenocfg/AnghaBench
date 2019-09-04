#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int tdp_limit; int near_tdp_limit_adjusted; scalar_t__ tdp_od_limit; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int si_calculate_adjusted_tdp_limits(struct amdgpu_device *adev,
					    bool adjust_polarity,
					    u32 tdp_adjustment,
					    u32 *tdp_limit,
					    u32 *near_tdp_limit)
{
	u32 adjustment_delta, max_tdp_limit;

	if (tdp_adjustment > (u32)adev->pm.dpm.tdp_od_limit)
		return -EINVAL;

	max_tdp_limit = ((100 + 100) * adev->pm.dpm.tdp_limit) / 100;

	if (adjust_polarity) {
		*tdp_limit = ((100 + tdp_adjustment) * adev->pm.dpm.tdp_limit) / 100;
		*near_tdp_limit = adev->pm.dpm.near_tdp_limit_adjusted + (*tdp_limit - adev->pm.dpm.tdp_limit);
	} else {
		*tdp_limit = ((100 - tdp_adjustment) * adev->pm.dpm.tdp_limit) / 100;
		adjustment_delta  = adev->pm.dpm.tdp_limit - *tdp_limit;
		if (adjustment_delta < adev->pm.dpm.near_tdp_limit_adjusted)
			*near_tdp_limit = adev->pm.dpm.near_tdp_limit_adjusted - adjustment_delta;
		else
			*near_tdp_limit = 0;
	}

	if ((*tdp_limit <= 0) || (*tdp_limit > max_tdp_limit))
		return -EINVAL;
	if ((*near_tdp_limit <= 0) || (*near_tdp_limit > *tdp_limit))
		return -EINVAL;

	return 0;
}