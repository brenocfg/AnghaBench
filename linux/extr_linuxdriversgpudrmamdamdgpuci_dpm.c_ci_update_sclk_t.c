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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ci_power_info {int /*<<< orphan*/  sram_end; scalar_t__ dpm_table_start; int /*<<< orphan*/  low_sclk_interrupt_t; scalar_t__ caps_sclk_throttle_low_notification; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LowSclkInterruptT ; 
 int /*<<< orphan*/  SMU7_Discrete_DpmTable ; 
 int amdgpu_ci_copy_bytes_to_smc (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_update_sclk_t(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	int ret = 0;
	u32 low_sclk_interrupt_t = 0;

	if (pi->caps_sclk_throttle_low_notification) {
		low_sclk_interrupt_t = cpu_to_be32(pi->low_sclk_interrupt_t);

		ret = amdgpu_ci_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   offsetof(SMU7_Discrete_DpmTable, LowSclkInterruptT),
					   (u8 *)&low_sclk_interrupt_t,
					   sizeof(u32), pi->sram_end);

	}

	return ret;
}