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
 int /*<<< orphan*/  R600_POWER_LEVEL_HIGH ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_LOW ; 
 int /*<<< orphan*/  R600_POWER_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  rv6xx_enable_dynamic_spread_spectrum (struct radeon_device*,int) ; 
 int /*<<< orphan*/  rv6xx_enable_engine_spread_spectrum (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv6xx_enable_memory_spread_spectrum (struct radeon_device*,int) ; 

__attribute__((used)) static void rv6xx_enable_spread_spectrum(struct radeon_device *rdev,
					 bool enable)
{
	if (enable)
		rv6xx_enable_dynamic_spread_spectrum(rdev, true);
	else {
		rv6xx_enable_engine_spread_spectrum(rdev, R600_POWER_LEVEL_LOW, false);
		rv6xx_enable_engine_spread_spectrum(rdev, R600_POWER_LEVEL_MEDIUM, false);
		rv6xx_enable_engine_spread_spectrum(rdev, R600_POWER_LEVEL_HIGH, false);
		rv6xx_enable_dynamic_spread_spectrum(rdev, false);
		rv6xx_enable_memory_spread_spectrum(rdev, false);
	}
}