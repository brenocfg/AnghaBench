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
struct si_power_info {int /*<<< orphan*/  sram_end; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_load_smc_ucode (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_reset_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  si_stop_smc_clock (struct radeon_device*) ; 

__attribute__((used)) static int si_upload_firmware(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	int ret;

	si_reset_smc(rdev);
	si_stop_smc_clock(rdev);

	ret = si_load_smc_ucode(rdev, si_pi->sram_end);

	return ret;
}