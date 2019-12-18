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
struct rv7xx_power_info {int /*<<< orphan*/  sram_end; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_load_smc_ucode (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_reset_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_stop_smc_clock (struct radeon_device*) ; 

int rv770_upload_firmware(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	int ret;

	rv770_reset_smc(rdev);
	rv770_stop_smc_clock(rdev);

	ret = rv770_load_smc_ucode(rdev, pi->sram_end);
	if (ret)
		return ret;

	return 0;
}