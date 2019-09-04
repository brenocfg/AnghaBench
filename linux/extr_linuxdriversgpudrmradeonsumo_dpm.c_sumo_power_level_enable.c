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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CG_SCLK_DPM_CTRL ; 
 int /*<<< orphan*/  SCLK_FSTATE_0_VLD ; 
 int /*<<< orphan*/  SCLK_FSTATE_1_VLD ; 
 int /*<<< orphan*/  SCLK_FSTATE_2_VLD ; 
 int /*<<< orphan*/  SCLK_FSTATE_3_VLD ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sumo_power_level_enable(struct radeon_device *rdev, u32 index, bool enable)
{
	u32 reg_index = index / 4;
	u32 field_index = index % 4;

	if (field_index == 0)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_0_VLD : 0, ~SCLK_FSTATE_0_VLD);
	else if (field_index == 1)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_1_VLD : 0, ~SCLK_FSTATE_1_VLD);
	else if (field_index == 2)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_2_VLD : 0, ~SCLK_FSTATE_2_VLD);
	else if (field_index == 3)
		WREG32_P(CG_SCLK_DPM_CTRL + (reg_index * 4),
			 enable ? SCLK_FSTATE_3_VLD : 0, ~SCLK_FSTATE_3_VLD);
}