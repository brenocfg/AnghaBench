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
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int CP_INT_CNTL__CNTX_BUSY_INT_ENABLE_MASK ; 
 int CP_INT_CNTL__CNTX_EMPTY_INT_ENABLE_MASK ; 
 int GFX_CLOCK_STATUS ; 
 int GFX_LS_STATUS ; 
 int GFX_POWER_STATUS ; 
 int RLC_BUSY_STATUS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_INT_CNTL_RING0 ; 
 int /*<<< orphan*/  mmDB_DEPTH_INFO ; 
 int /*<<< orphan*/  mmRLC_STAT ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v6_0_enable_gui_idle_interrupt(struct amdgpu_device *adev,
					       bool enable)
{
	u32 tmp = RREG32(mmCP_INT_CNTL_RING0);
	u32 mask;
	int i;

	if (enable)
		tmp |= (CP_INT_CNTL__CNTX_BUSY_INT_ENABLE_MASK |
			CP_INT_CNTL__CNTX_EMPTY_INT_ENABLE_MASK);
	else
		tmp &= ~(CP_INT_CNTL__CNTX_BUSY_INT_ENABLE_MASK |
			 CP_INT_CNTL__CNTX_EMPTY_INT_ENABLE_MASK);
	WREG32(mmCP_INT_CNTL_RING0, tmp);

	if (!enable) {
		/* read a gfx register */
		tmp = RREG32(mmDB_DEPTH_INFO);

		mask = RLC_BUSY_STATUS | GFX_POWER_STATUS | GFX_CLOCK_STATUS | GFX_LS_STATUS;
		for (i = 0; i < adev->usec_timeout; i++) {
			if ((RREG32(mmRLC_STAT) & mask) == (GFX_CLOCK_STATUS | GFX_POWER_STATUS))
				break;
			udelay(1);
		}
	}
}