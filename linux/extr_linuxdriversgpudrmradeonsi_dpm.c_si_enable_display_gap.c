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
 int DISP1_GAP (int /*<<< orphan*/ ) ; 
 int DISP1_GAP_MASK ; 
 int DISP1_GAP_MCHG (int /*<<< orphan*/ ) ; 
 int DISP1_GAP_MCHG_MASK ; 
 int DISP2_GAP (int /*<<< orphan*/ ) ; 
 int DISP2_GAP_MASK ; 
 int DISP2_GAP_MCHG (int /*<<< orphan*/ ) ; 
 int DISP2_GAP_MCHG_MASK ; 
 int /*<<< orphan*/  R600_PM_DISPLAY_GAP_IGNORE ; 
 int /*<<< orphan*/  R600_PM_DISPLAY_GAP_VBLANK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_enable_display_gap(struct radeon_device *rdev)
{
	u32 tmp = RREG32(CG_DISPLAY_GAP_CNTL);

	tmp &= ~(DISP1_GAP_MASK | DISP2_GAP_MASK);
	tmp |= (DISP1_GAP(R600_PM_DISPLAY_GAP_IGNORE) |
		DISP2_GAP(R600_PM_DISPLAY_GAP_IGNORE));

	tmp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	tmp |= (DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_VBLANK) |
		DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE));
	WREG32(CG_DISPLAY_GAP_CNTL, tmp);
}