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
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_MC_LS ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_cg_ls_en ; 
 int /*<<< orphan*/ * mc_cg_registers ; 

__attribute__((used)) static void gmc_v7_0_enable_mc_ls(struct amdgpu_device *adev,
				  bool enable)
{
	int i;
	u32 orig, data;

	for (i = 0; i < ARRAY_SIZE(mc_cg_registers); i++) {
		orig = data = RREG32(mc_cg_registers[i]);
		if (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_LS))
			data |= mc_cg_ls_en[i];
		else
			data &= ~mc_cg_ls_en[i];
		if (data != orig)
			WREG32(mc_cg_registers[i], data);
	}
}