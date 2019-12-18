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
struct radeon_device {int dummy; } ;
struct ci_power_info {int /*<<< orphan*/  sram_end; int /*<<< orphan*/  arb_table_start; } ;

/* Variables and functions */
 int MC_CG_ARB_FREQ_F1 ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_read_smc_sram_dword (struct radeon_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int ci_write_smc_sram_dword (struct radeon_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_init_arb_table_index(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp;
	int ret;

	ret = ci_read_smc_sram_dword(rdev, pi->arb_table_start,
				     &tmp, pi->sram_end);
	if (ret)
		return ret;

	tmp &= 0x00FFFFFF;
	tmp |= MC_CG_ARB_FREQ_F1 << 24;

	return ci_write_smc_sram_dword(rdev, pi->arb_table_start,
				       tmp, pi->sram_end);
}