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
 int ENABLE_FV_THROT ; 
 int ENABLE_FV_UPDATE ; 
 int /*<<< orphan*/  FVTHROT_CNTRL_REG ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rs780_clk_scaling_enable(struct radeon_device *rdev, bool enable)
{
	if (enable)
		WREG32_P(FVTHROT_CNTRL_REG, ENABLE_FV_THROT | ENABLE_FV_UPDATE,
			 ~(ENABLE_FV_THROT | ENABLE_FV_UPDATE));
	else
		WREG32_P(FVTHROT_CNTRL_REG, 0,
			 ~(ENABLE_FV_THROT | ENABLE_FV_UPDATE));
}