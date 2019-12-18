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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CFG_VGA_IO_DIS ; 
 int /*<<< orphan*/  RADEON_CFG_VGA_RAM_EN ; 
 int /*<<< orphan*/  RADEON_CONFIG_CNTL ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r100_vga_set_state(struct radeon_device *rdev, bool state)
{
	uint32_t temp;

	temp = RREG32(RADEON_CONFIG_CNTL);
	if (state == false) {
		temp &= ~RADEON_CFG_VGA_RAM_EN;
		temp |= RADEON_CFG_VGA_IO_DIS;
	} else {
		temp &= ~RADEON_CFG_VGA_IO_DIS;
	}
	WREG32(RADEON_CONFIG_CNTL, temp);
}