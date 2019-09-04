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
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_3 ; 
 int DPM_SCLK_ENABLE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sumo_dpm_enabled(struct radeon_device *rdev)
{
	if (RREG32(CG_SCLK_DPM_CTRL_3) & DPM_SCLK_ENABLE)
		return true;
	else
		return false;
}