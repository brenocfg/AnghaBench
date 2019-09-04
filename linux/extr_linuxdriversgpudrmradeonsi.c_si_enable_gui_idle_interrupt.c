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
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int CNTX_BUSY_INT_ENABLE ; 
 int CNTX_EMPTY_INT_ENABLE ; 
 int /*<<< orphan*/  CP_INT_CNTL_RING0 ; 
 int /*<<< orphan*/  DB_DEPTH_INFO ; 
 int GFX_CLOCK_STATUS ; 
 int GFX_LS_STATUS ; 
 int GFX_POWER_STATUS ; 
 int RLC_BUSY_STATUS ; 
 int /*<<< orphan*/  RLC_STAT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void si_enable_gui_idle_interrupt(struct radeon_device *rdev,
					 bool enable)
{
	u32 tmp = RREG32(CP_INT_CNTL_RING0);
	u32 mask;
	int i;

	if (enable)
		tmp |= (CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	else
		tmp &= ~(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, tmp);

	if (!enable) {
		/* read a gfx register */
		tmp = RREG32(DB_DEPTH_INFO);

		mask = RLC_BUSY_STATUS | GFX_POWER_STATUS | GFX_CLOCK_STATUS | GFX_LS_STATUS;
		for (i = 0; i < rdev->usec_timeout; i++) {
			if ((RREG32(RLC_STAT) & mask) == (GFX_CLOCK_STATUS | GFX_POWER_STATUS))
				break;
			udelay(1);
		}
	}
}