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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_PWR_GATING_CNTL ; 
 int /*<<< orphan*/  DYN_PWR_DOWN_EN ; 
 int /*<<< orphan*/  GB_ADDR_CONFIG ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sumo_gfx_powergating_enable(struct radeon_device *rdev, bool enable)
{
	if (enable)
		WREG32_P(CG_PWR_GATING_CNTL, DYN_PWR_DOWN_EN, ~DYN_PWR_DOWN_EN);
	else {
		WREG32_P(CG_PWR_GATING_CNTL, 0, ~DYN_PWR_DOWN_EN);
		RREG32(GB_ADDR_CONFIG);
	}
}