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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_HDP_MGCG ; 
 int /*<<< orphan*/  HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmHDP_HOST_PATH_CNTL ; 

__attribute__((used)) static void vi_update_hdp_medium_grain_clock_gating(struct amdgpu_device *adev,
						    bool enable)
{
	uint32_t temp, data;

	temp = data = RREG32(mmHDP_HOST_PATH_CNTL);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_HDP_MGCG))
		data &= ~HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK;
	else
		data |= HDP_HOST_PATH_CNTL__CLOCK_GATING_DIS_MASK;

	if (temp != data)
		WREG32(mmHDP_HOST_PATH_CNTL, data);
}