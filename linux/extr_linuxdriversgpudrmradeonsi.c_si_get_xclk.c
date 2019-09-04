#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int reference_freq; } ;
struct TYPE_4__ {TYPE_1__ spll; } ;
struct radeon_device {TYPE_2__ clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_CLKPIN_CNTL ; 
 int /*<<< orphan*/  CG_CLKPIN_CNTL_2 ; 
 int MUX_TCLK_TO_XCLK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int TCLK ; 
 int XTALIN_DIVIDE ; 

u32 si_get_xclk(struct radeon_device *rdev)
{
	u32 reference_clock = rdev->clock.spll.reference_freq;
	u32 tmp;

	tmp = RREG32(CG_CLKPIN_CNTL_2);
	if (tmp & MUX_TCLK_TO_XCLK)
		return TCLK;

	tmp = RREG32(CG_CLKPIN_CNTL);
	if (tmp & XTALIN_DIVIDE)
		return reference_clock / 4;

	return reference_clock;
}