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
 int /*<<< orphan*/  BLACKOUT_MODE ; 
 int /*<<< orphan*/  MC_SHARED_BLACKOUT_CNTL ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gmc_v7_0_wait_for_idle (void*) ; 
 int /*<<< orphan*/  mmBIF_FB_EN ; 
 int /*<<< orphan*/  mmMC_SHARED_BLACKOUT_CNTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gmc_v7_0_mc_stop(struct amdgpu_device *adev)
{
	u32 blackout;

	gmc_v7_0_wait_for_idle((void *)adev);

	blackout = RREG32(mmMC_SHARED_BLACKOUT_CNTL);
	if (REG_GET_FIELD(blackout, MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE) != 1) {
		/* Block CPU access */
		WREG32(mmBIF_FB_EN, 0);
		/* blackout the MC */
		blackout = REG_SET_FIELD(blackout,
					 MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE, 0);
		WREG32(mmMC_SHARED_BLACKOUT_CNTL, blackout | 1);
	}
	/* wait for the MC to settle */
	udelay(100);
}