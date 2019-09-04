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
struct rv6xx_power_info {int restricted_levels; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_POWER_LEVEL_HIGH ; 
 int /*<<< orphan*/  r600_power_level_enable (struct radeon_device*,int /*<<< orphan*/ ,int) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_enable_high(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);

	if ((pi->restricted_levels < 1) ||
	    (pi->restricted_levels == 3))
		r600_power_level_enable(rdev, R600_POWER_LEVEL_HIGH, true);
}