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
typedef  scalar_t__ uint32_t ;
struct radeon_device {scalar_t__ family; int /*<<< orphan*/ * bios_scratch; } ;

/* Variables and functions */
 scalar_t__ CHIP_R600 ; 
 scalar_t__ R600_BIOS_0_SCRATCH ; 
 scalar_t__ RADEON_BIOS_0_SCRATCH ; 
 int RADEON_BIOS_NUM_SCRATCH ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 

void radeon_restore_bios_scratch_regs(struct radeon_device *rdev)
{
	uint32_t scratch_reg;
	int i;

	if (rdev->family >= CHIP_R600)
		scratch_reg = R600_BIOS_0_SCRATCH;
	else
		scratch_reg = RADEON_BIOS_0_SCRATCH;

	for (i = 0; i < RADEON_BIOS_NUM_SCRATCH; i++)
		WREG32(scratch_reg + (i * 4), rdev->bios_scratch[i]);
}