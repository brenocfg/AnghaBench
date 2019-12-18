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
typedef  scalar_t__ u16 ;
struct radeon_device {int dummy; } ;
struct ci_power_info {int /*<<< orphan*/  sram_end; scalar_t__ soft_regs_start; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_write_smc_sram_dword (struct radeon_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_write_smc_soft_register(struct radeon_device *rdev,
				      u16 reg_offset, u32 value)
{
	struct ci_power_info *pi = ci_get_pi(rdev);

	return ci_write_smc_sram_dword(rdev,
				       pi->soft_regs_start + reg_offset,
				       value, pi->sram_end);
}