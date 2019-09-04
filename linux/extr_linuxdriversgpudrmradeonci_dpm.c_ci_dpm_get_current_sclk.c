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

/* Variables and functions */
 int /*<<< orphan*/  ci_get_average_sclk_freq (struct radeon_device*) ; 

u32 ci_dpm_get_current_sclk(struct radeon_device *rdev)
{
	u32 sclk = ci_get_average_sclk_freq(rdev);

	return sclk;
}