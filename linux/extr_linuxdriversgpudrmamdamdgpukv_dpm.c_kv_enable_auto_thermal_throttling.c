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
struct kv_power_info {int graphics_therm_throttle_enable; int /*<<< orphan*/  sram_end; scalar_t__ dpm_table_start; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsThermThrottleEnable ; 
 int /*<<< orphan*/  SMU7_Fusion_DpmTable ; 
 int amdgpu_kv_copy_bytes_to_smc (struct amdgpu_device*,scalar_t__,int*,int,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_enable_auto_thermal_throttling(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	int ret;

	pi->graphics_therm_throttle_enable = 1;

	ret = amdgpu_kv_copy_bytes_to_smc(adev,
				   pi->dpm_table_start +
				   offsetof(SMU7_Fusion_DpmTable, GraphicsThermThrottleEnable),
				   &pi->graphics_therm_throttle_enable,
				   sizeof(u8), pi->sram_end);

	return ret;
}