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
 int MC_CG_ARB_FREQ_F0 ; 
 int ni_copy_and_switch_arb_sets (struct radeon_device*,int,int) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_read_smc_sram_dword (struct radeon_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_force_switch_to_arb_f0(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	u32 tmp;
	int ret;

	ret = si_read_smc_sram_dword(rdev, si_pi->arb_table_start,
				     &tmp, si_pi->sram_end);
	if (ret)
		return ret;

	tmp = (tmp >> 24) & 0xff;

	if (tmp == MC_CG_ARB_FREQ_F0)
		return 0;

	return ni_copy_and_switch_arb_sets(rdev, tmp, MC_CG_ARB_FREQ_F0);
}