#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* backbias; } ;
struct rv6xx_power_info {TYPE_1__ hw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIGH_BACKBIAS_VALUE ; 
 int /*<<< orphan*/  MEDIUM_BACKBIAS_VALUE ; 
 int /*<<< orphan*/  VID_UPPER_GPIO_CNTL ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_program_backbias_stepping_parameters_except_lowest_entry(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	if (pi->hw.backbias[1])
		WREG32_P(VID_UPPER_GPIO_CNTL, MEDIUM_BACKBIAS_VALUE, ~MEDIUM_BACKBIAS_VALUE);
	else
		WREG32_P(VID_UPPER_GPIO_CNTL, 0, ~MEDIUM_BACKBIAS_VALUE);

	if (pi->hw.backbias[2])
		WREG32_P(VID_UPPER_GPIO_CNTL, HIGH_BACKBIAS_VALUE, ~HIGH_BACKBIAS_VALUE);
	else
		WREG32_P(VID_UPPER_GPIO_CNTL, 0, ~HIGH_BACKBIAS_VALUE);
}