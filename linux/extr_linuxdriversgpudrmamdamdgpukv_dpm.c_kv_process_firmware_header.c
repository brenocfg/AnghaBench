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
typedef  void* u32 ;
struct kv_power_info {void* soft_regs_start; int /*<<< orphan*/  sram_end; void* dpm_table_start; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DpmTable ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU7_Firmware_Header ; 
 int /*<<< orphan*/  SoftRegisters ; 
 int amdgpu_kv_read_smc_sram_dword (struct amdgpu_device*,scalar_t__,void**,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_process_firmware_header(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 tmp;
	int ret;

	ret = amdgpu_kv_read_smc_sram_dword(adev, SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, DpmTable),
				     &tmp, pi->sram_end);

	if (ret == 0)
		pi->dpm_table_start = tmp;

	ret = amdgpu_kv_read_smc_sram_dword(adev, SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, SoftRegisters),
				     &tmp, pi->sram_end);

	if (ret == 0)
		pi->soft_regs_start = tmp;

	return ret;
}