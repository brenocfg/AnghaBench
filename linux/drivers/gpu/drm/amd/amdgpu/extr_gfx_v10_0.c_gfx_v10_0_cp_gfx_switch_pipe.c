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
typedef  int /*<<< orphan*/  CP_PIPE_ID ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  GRBM_GFX_CNTL ; 
 int /*<<< orphan*/  PIPEID ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGRBM_GFX_CNTL ; 

__attribute__((used)) static void gfx_v10_0_cp_gfx_switch_pipe(struct amdgpu_device *adev,
					 CP_PIPE_ID pipe)
{
	u32 tmp;

	tmp = RREG32_SOC15(GC, 0, mmGRBM_GFX_CNTL);
	tmp = REG_SET_FIELD(tmp, GRBM_GFX_CNTL, PIPEID, pipe);

	WREG32_SOC15(GC, 0, mmGRBM_GFX_CNTL, tmp);
}