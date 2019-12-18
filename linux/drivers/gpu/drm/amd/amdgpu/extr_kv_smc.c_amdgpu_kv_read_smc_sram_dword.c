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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int kv_set_smc_sram_address (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMC_IND_DATA_0 ; 

int amdgpu_kv_read_smc_sram_dword(struct amdgpu_device *adev, u32 smc_address,
			   u32 *value, u32 limit)
{
	int ret;

	ret = kv_set_smc_sram_address(adev, smc_address, limit);
	if (ret)
		return ret;

	*value = RREG32(mmSMC_IND_DATA_0);
	return 0;
}