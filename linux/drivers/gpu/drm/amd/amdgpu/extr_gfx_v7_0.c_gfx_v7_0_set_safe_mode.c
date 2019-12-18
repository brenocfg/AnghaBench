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
typedef  scalar_t__ u32 ;
struct amdgpu_device {scalar_t__ usec_timeout; } ;

/* Variables and functions */
 scalar_t__ RLC_GPM_STAT__GFX_CLOCK_STATUS_MASK ; 
 scalar_t__ RLC_GPM_STAT__GFX_POWER_STATUS_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmRLC_GPM_STAT ; 
 int /*<<< orphan*/  mmRLC_GPR_REG2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v7_0_set_safe_mode(struct amdgpu_device *adev)
{
	u32 tmp, i, mask;

	tmp = 0x1 | (1 << 1);
	WREG32(mmRLC_GPR_REG2, tmp);

	mask = RLC_GPM_STAT__GFX_POWER_STATUS_MASK |
		RLC_GPM_STAT__GFX_CLOCK_STATUS_MASK;
	for (i = 0; i < adev->usec_timeout; i++) {
		if ((RREG32(mmRLC_GPM_STAT) & mask) == mask)
			break;
		udelay(1);
	}

	for (i = 0; i < adev->usec_timeout; i++) {
		if ((RREG32(mmRLC_GPR_REG2) & 0x1) == 0)
			break;
		udelay(1);
	}
}