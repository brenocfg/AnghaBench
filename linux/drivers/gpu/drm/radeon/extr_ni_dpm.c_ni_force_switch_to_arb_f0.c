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
struct rv7xx_power_info {int /*<<< orphan*/  sram_end; } ;
struct radeon_device {int dummy; } ;
struct ni_power_info {int /*<<< orphan*/  arb_table_start; } ;

/* Variables and functions */
 int MC_CG_ARB_FREQ_F0 ; 
 int ni_copy_and_switch_arb_sets (struct radeon_device*,int,int) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_read_smc_sram_dword (struct radeon_device*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_force_switch_to_arb_f0(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	u32 tmp;
	int ret;

	ret = rv770_read_smc_sram_dword(rdev, ni_pi->arb_table_start,
					&tmp, pi->sram_end);
	if (ret)
		return ret;

	tmp = (tmp >> 24) & 0xff;

	if (tmp == MC_CG_ARB_FREQ_F0)
		return 0;

	return ni_copy_and_switch_arb_sets(rdev, tmp, MC_CG_ARB_FREQ_F0);
}