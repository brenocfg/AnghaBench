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
struct rv6xx_sclk_stepping {scalar_t__ vco_frequency; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool rv6xx_reached_stepping_target(struct radeon_device *rdev,
					  struct rv6xx_sclk_stepping *cur,
					  struct rv6xx_sclk_stepping *target,
					  bool increasing_vco)
{
	return (increasing_vco && (cur->vco_frequency >= target->vco_frequency)) ||
		(!increasing_vco && (cur->vco_frequency <= target->vco_frequency));
}