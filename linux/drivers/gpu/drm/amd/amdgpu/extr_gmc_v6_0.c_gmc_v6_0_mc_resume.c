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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_FB_EN ; 
 int /*<<< orphan*/  BLACKOUT_MODE ; 
 int /*<<< orphan*/  FB_READ_EN ; 
 int /*<<< orphan*/  FB_WRITE_EN ; 
 int /*<<< orphan*/  MC_SHARED_BLACKOUT_CNTL ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmBIF_FB_EN ; 
 int /*<<< orphan*/  mmMC_SHARED_BLACKOUT_CNTL ; 

__attribute__((used)) static void gmc_v6_0_mc_resume(struct amdgpu_device *adev)
{
	u32 tmp;

	/* unblackout the MC */
	tmp = RREG32(mmMC_SHARED_BLACKOUT_CNTL);
	tmp = REG_SET_FIELD(tmp, MC_SHARED_BLACKOUT_CNTL, BLACKOUT_MODE, 0);
	WREG32(mmMC_SHARED_BLACKOUT_CNTL, tmp);
	/* allow CPU access */
	tmp = REG_SET_FIELD(0, BIF_FB_EN, FB_READ_EN, 1);
	tmp = REG_SET_FIELD(tmp, BIF_FB_EN, FB_WRITE_EN, 1);
	WREG32(mmBIF_FB_EN, tmp);
}