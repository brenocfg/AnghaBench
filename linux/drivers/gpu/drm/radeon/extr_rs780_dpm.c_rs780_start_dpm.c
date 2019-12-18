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
 int /*<<< orphan*/  r600_dynamicpm_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_enable_mclk_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_enable_sclk_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_enable_spll_bypass (struct radeon_device*,int) ; 
 int /*<<< orphan*/  r600_wait_for_spll_change (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wait_for_vblank (struct radeon_device*,int) ; 

__attribute__((used)) static void rs780_start_dpm(struct radeon_device *rdev)
{
	r600_enable_sclk_control(rdev, false);
	r600_enable_mclk_control(rdev, false);

	r600_dynamicpm_enable(rdev, true);

	radeon_wait_for_vblank(rdev, 0);
	radeon_wait_for_vblank(rdev, 1);

	r600_enable_spll_bypass(rdev, true);
	r600_wait_for_spll_change(rdev);
	r600_enable_spll_bypass(rdev, false);
	r600_wait_for_spll_change(rdev);

	r600_enable_spll_bypass(rdev, true);
	r600_wait_for_spll_change(rdev);
	r600_enable_spll_bypass(rdev, false);
	r600_wait_for_spll_change(rdev);

	r600_enable_sclk_control(rdev, true);
}