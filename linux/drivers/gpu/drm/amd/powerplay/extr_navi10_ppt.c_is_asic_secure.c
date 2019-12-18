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
typedef  int uint32_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int MP0_Public ; 
 int RREG32_PCIE (int) ; 
 int smnMP0_FW_INTF ; 

__attribute__((used)) static bool is_asic_secure(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	bool is_secure = true;
	uint32_t mp0_fw_intf;

	mp0_fw_intf = RREG32_PCIE(MP0_Public |
				   (smnMP0_FW_INTF & 0xffffffff));

	if (!(mp0_fw_intf & (1 << 19)))
		is_secure = false;

	return is_secure;
}