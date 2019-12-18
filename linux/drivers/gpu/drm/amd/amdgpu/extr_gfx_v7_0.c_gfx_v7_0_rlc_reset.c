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
 int /*<<< orphan*/  GRBM_SOFT_RESET__SOFT_RESET_RLC_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGRBM_SOFT_RESET ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v7_0_rlc_reset(struct amdgpu_device *adev)
{
	u32 tmp = RREG32(mmGRBM_SOFT_RESET);

	tmp |= GRBM_SOFT_RESET__SOFT_RESET_RLC_MASK;
	WREG32(mmGRBM_SOFT_RESET, tmp);
	udelay(50);
	tmp &= ~GRBM_SOFT_RESET__SOFT_RESET_RLC_MASK;
	WREG32(mmGRBM_SOFT_RESET, tmp);
	udelay(50);
}