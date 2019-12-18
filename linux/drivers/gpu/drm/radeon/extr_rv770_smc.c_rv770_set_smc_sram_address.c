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
typedef  int u16 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SMC_SRAM_ADDR ; 
 int SMC_SRAM_AUTO_INC_DIS ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rv770_set_smc_sram_address(struct radeon_device *rdev,
				      u16 smc_address, u16 limit)
{
	u32 addr;

	if (smc_address & 3)
		return -EINVAL;
	if ((smc_address + 3) > limit)
		return -EINVAL;

	addr = smc_address;
	addr |= SMC_SRAM_AUTO_INC_DIS;

	WREG32(SMC_SRAM_ADDR, addr);

	return 0;
}