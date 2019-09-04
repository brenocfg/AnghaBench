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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int MC_CG_ARB_FREQ_F1 ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_read_smc_sram_dword (struct radeon_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int si_write_smc_sram_dword (struct radeon_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_init_arb_table_index(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	u32 tmp;
	int ret;

	ret = si_read_smc_sram_dword(rdev, si_pi->arb_table_start, &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	tmp &= 0x00FFFFFF;
	tmp |= MC_CG_ARB_FREQ_F1 << 24;

	return si_write_smc_sram_dword(rdev, si_pi->arb_table_start,  tmp, si_pi->sram_end);
}