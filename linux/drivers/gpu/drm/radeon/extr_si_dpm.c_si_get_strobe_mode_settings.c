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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct rv7xx_power_info {scalar_t__ mclk_strobe_mode_threshold; scalar_t__ mem_gddr5; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISLANDS_SMC_STROBE_ENABLE ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  si_get_ddr3_mclk_frequency_ratio (scalar_t__) ; 
 int /*<<< orphan*/  si_get_mclk_frequency_ratio (scalar_t__,int) ; 

__attribute__((used)) static u8 si_get_strobe_mode_settings(struct radeon_device *rdev, u32 mclk)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	bool strobe_mode = false;
	u8 result = 0;

	if (mclk <= pi->mclk_strobe_mode_threshold)
		strobe_mode = true;

	if (pi->mem_gddr5)
		result = si_get_mclk_frequency_ratio(mclk, strobe_mode);
	else
		result = si_get_ddr3_mclk_frequency_ratio(mclk);

	if (strobe_mode)
		result |= SISLANDS_SMC_STROBE_ENABLE;

	return result;
}