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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF ; 
 int /*<<< orphan*/  FabricConfigAccessControl__CfgRegInstAccEn_MASK ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmFabricConfigAccessControl ; 
 int /*<<< orphan*/  mmFabricConfigAccessControl_DEFAULT ; 

__attribute__((used)) static void df_v1_7_enable_broadcast_mode(struct amdgpu_device *adev,
                                          bool enable)
{
	u32 tmp;

	if (enable) {
		tmp = RREG32_SOC15(DF, 0, mmFabricConfigAccessControl);
		tmp &= ~FabricConfigAccessControl__CfgRegInstAccEn_MASK;
		WREG32_SOC15(DF, 0, mmFabricConfigAccessControl, tmp);
	} else
		WREG32_SOC15(DF, 0, mmFabricConfigAccessControl,
			     mmFabricConfigAccessControl_DEFAULT);
}