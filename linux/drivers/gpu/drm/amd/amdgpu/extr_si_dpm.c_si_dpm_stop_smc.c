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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_si_reset_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_si_smc_clock (struct amdgpu_device*,int) ; 

__attribute__((used)) static void si_dpm_stop_smc(struct amdgpu_device *adev)
{
	amdgpu_si_reset_smc(adev);
	amdgpu_si_smc_clock(adev, false);
}