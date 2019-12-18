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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct igp_power_info {int /*<<< orphan*/  bootup_uma_clk; } ;

/* Variables and functions */
 struct igp_power_info* rs780_get_pi (struct radeon_device*) ; 

u32 rs780_dpm_get_mclk(struct radeon_device *rdev, bool low)
{
	struct igp_power_info *pi = rs780_get_pi(rdev);

	return pi->bootup_uma_clk;
}