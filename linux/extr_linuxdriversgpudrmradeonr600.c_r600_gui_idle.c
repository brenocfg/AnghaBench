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
 int /*<<< orphan*/  GRBM_STATUS ; 
 int GUI_ACTIVE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

bool r600_gui_idle(struct radeon_device *rdev)
{
	if (RREG32(GRBM_STATUS) & GUI_ACTIVE)
		return false;
	else
		return true;
}