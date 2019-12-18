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
 int /*<<< orphan*/  CG_MPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  SSEN ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv6xx_enable_memory_spread_spectrum(struct radeon_device *rdev,
						bool enable)
{
	if (enable)
		WREG32_P(CG_MPLL_SPREAD_SPECTRUM, SSEN, ~SSEN);
	else
		WREG32_P(CG_MPLL_SPREAD_SPECTRUM, 0, ~SSEN);
}