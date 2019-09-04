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
struct kv_power_info {int /*<<< orphan*/  sram_end; scalar_t__ dpm_table_start; int /*<<< orphan*/  low_sclk_interrupt_t; scalar_t__ caps_sclk_throttle_low_notification; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LowSclkInterruptT ; 
 int /*<<< orphan*/  SMU7_Fusion_DpmTable ; 
 int amdgpu_kv_copy_bytes_to_smc (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_update_sclk_t(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 low_sclk_interrupt_t = 0;
	int ret = 0;

	if (pi->caps_sclk_throttle_low_notification) {
		low_sclk_interrupt_t = cpu_to_be32(pi->low_sclk_interrupt_t);

		ret = amdgpu_kv_copy_bytes_to_smc(adev,
					   pi->dpm_table_start +
					   offsetof(SMU7_Fusion_DpmTable, LowSclkInterruptT),
					   (u8 *)&low_sclk_interrupt_t,
					   sizeof(u32), pi->sram_end);
	}
	return ret;
}