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
 int AMD_CG_SUPPORT_HDP_LS ; 
 int /*<<< orphan*/  HDP_MEM_POWER_LS__LS_ENABLE_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmHDP_MEM_POWER_LS ; 

__attribute__((used)) static void vi_update_hdp_light_sleep(struct amdgpu_device *adev,
				      bool enable)
{
	uint32_t temp, data;

	temp = data = RREG32(mmHDP_MEM_POWER_LS);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS))
		data |= HDP_MEM_POWER_LS__LS_ENABLE_MASK;
	else
		data &= ~HDP_MEM_POWER_LS__LS_ENABLE_MASK;

	if (temp != data)
		WREG32(mmHDP_MEM_POWER_LS, data);
}