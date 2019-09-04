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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int AMDGPU_PM_DISPLAY_GAP_IGNORE ; 
 int AMDGPU_PM_DISPLAY_GAP_VBLANK ; 
 int CG_DISPLAY_GAP_CNTL__DISP_GAP_MASK ; 
 int CG_DISPLAY_GAP_CNTL__DISP_GAP_MCHG_MASK ; 
 int CG_DISPLAY_GAP_CNTL__DISP_GAP_MCHG__SHIFT ; 
 int CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixCG_DISPLAY_GAP_CNTL ; 

__attribute__((used)) static void ci_enable_display_gap(struct amdgpu_device *adev)
{
	u32 tmp = RREG32_SMC(ixCG_DISPLAY_GAP_CNTL);

	tmp &= ~(CG_DISPLAY_GAP_CNTL__DISP_GAP_MASK |
			CG_DISPLAY_GAP_CNTL__DISP_GAP_MCHG_MASK);
	tmp |= ((AMDGPU_PM_DISPLAY_GAP_IGNORE << CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT) |
		(AMDGPU_PM_DISPLAY_GAP_VBLANK << CG_DISPLAY_GAP_CNTL__DISP_GAP_MCHG__SHIFT));

	WREG32_SMC(ixCG_DISPLAY_GAP_CNTL, tmp);
}