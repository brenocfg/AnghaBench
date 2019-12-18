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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DISPLAY_GAP_CNTL ; 
 int DISP_GAP (int /*<<< orphan*/ ) ; 
 int DISP_GAP_MASK ; 
 int DISP_GAP_MCHG (int /*<<< orphan*/ ) ; 
 int DISP_GAP_MCHG_MASK ; 
 int /*<<< orphan*/  R600_PM_DISPLAY_GAP_IGNORE ; 
 int /*<<< orphan*/  R600_PM_DISPLAY_GAP_VBLANK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ci_enable_display_gap(struct radeon_device *rdev)
{
	u32 tmp = RREG32_SMC(CG_DISPLAY_GAP_CNTL);

	tmp &= ~(DISP_GAP_MASK | DISP_GAP_MCHG_MASK);
	tmp |= (DISP_GAP(R600_PM_DISPLAY_GAP_IGNORE) |
		DISP_GAP_MCHG(R600_PM_DISPLAY_GAP_VBLANK));

	WREG32_SMC(CG_DISPLAY_GAP_CNTL, tmp);
}