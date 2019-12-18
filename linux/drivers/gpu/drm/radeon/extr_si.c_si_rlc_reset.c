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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRBM_SOFT_RESET ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_RESET_RLC ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void si_rlc_reset(struct radeon_device *rdev)
{
	u32 tmp = RREG32(GRBM_SOFT_RESET);

	tmp |= SOFT_RESET_RLC;
	WREG32(GRBM_SOFT_RESET, tmp);
	udelay(50);
	tmp &= ~SOFT_RESET_RLC;
	WREG32(GRBM_SOFT_RESET, tmp);
	udelay(50);
}