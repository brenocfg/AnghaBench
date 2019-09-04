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
 int /*<<< orphan*/  rv770_reset_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_stop_smc_clock (struct radeon_device*) ; 

void r7xx_stop_smc(struct radeon_device *rdev)
{
	rv770_reset_smc(rdev);
	rv770_stop_smc_clock(rdev);
}