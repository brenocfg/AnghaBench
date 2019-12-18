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
typedef  int u32 ;
struct si_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  arb_table_start; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int MC_CG_ARB_FREQ_F1 ; 
 int amdgpu_si_read_smc_sram_dword (struct amdgpu_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int amdgpu_si_write_smc_sram_dword (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_init_arb_table_index(struct amdgpu_device *adev)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	u32 tmp;
	int ret;

	ret = amdgpu_si_read_smc_sram_dword(adev, si_pi->arb_table_start,
					    &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	tmp &= 0x00FFFFFF;
	tmp |= MC_CG_ARB_FREQ_F1 << 24;

	return amdgpu_si_write_smc_sram_dword(adev, si_pi->arb_table_start,
					      tmp, si_pi->sram_end);
}