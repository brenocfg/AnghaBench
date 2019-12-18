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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int amdgpu_si_load_smc_ucode (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_si_reset_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_si_smc_clock (struct amdgpu_device*,int) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_upload_firmware(struct amdgpu_device *adev)
{
	struct si_power_info *si_pi = si_get_pi(adev);

	amdgpu_si_reset_smc(adev);
	amdgpu_si_smc_clock(adev, false);

	return amdgpu_si_load_smc_ucode(adev, si_pi->sram_end);
}