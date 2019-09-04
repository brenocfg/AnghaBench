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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RREG32 (scalar_t__) ; 
 scalar_t__ SDMA0_ME_CNTL ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 scalar_t__ SDMA_HALT ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cik_sdma_ctx_switch_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_sdma_gfx_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_sdma_rlc_stop (struct radeon_device*) ; 

void cik_sdma_enable(struct radeon_device *rdev, bool enable)
{
	u32 me_cntl, reg_offset;
	int i;

	if (enable == false) {
		cik_sdma_gfx_stop(rdev);
		cik_sdma_rlc_stop(rdev);
	}

	for (i = 0; i < 2; i++) {
		if (i == 0)
			reg_offset = SDMA0_REGISTER_OFFSET;
		else
			reg_offset = SDMA1_REGISTER_OFFSET;
		me_cntl = RREG32(SDMA0_ME_CNTL + reg_offset);
		if (enable)
			me_cntl &= ~SDMA_HALT;
		else
			me_cntl |= SDMA_HALT;
		WREG32(SDMA0_ME_CNTL + reg_offset, me_cntl);
	}

	cik_sdma_ctx_switch_enable(rdev, enable);
}