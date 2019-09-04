#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int vram_is_ddr; int vram_width; } ;
struct radeon_device {int flags; scalar_t__ family; TYPE_1__ mc; } ;

/* Variables and functions */
 scalar_t__ CHIP_RS100 ; 
 scalar_t__ CHIP_RS200 ; 
 scalar_t__ CHIP_RV100 ; 
 scalar_t__ CHIP_RV280 ; 
 int RADEON_IS_IGP ; 
 int RADEON_MEM_CFG_TYPE_DDR ; 
 int /*<<< orphan*/  RADEON_MEM_CNTL ; 
 int RADEON_MEM_NUM_CHANNELS_MASK ; 
 int /*<<< orphan*/  RADEON_MEM_SDRAM_MODE_REG ; 
 int RADEON_SINGLE_CRTC ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RV100_HALF_MODE ; 

__attribute__((used)) static void r100_vram_get_type(struct radeon_device *rdev)
{
	uint32_t tmp;

	rdev->mc.vram_is_ddr = false;
	if (rdev->flags & RADEON_IS_IGP)
		rdev->mc.vram_is_ddr = true;
	else if (RREG32(RADEON_MEM_SDRAM_MODE_REG) & RADEON_MEM_CFG_TYPE_DDR)
		rdev->mc.vram_is_ddr = true;
	if ((rdev->family == CHIP_RV100) ||
	    (rdev->family == CHIP_RS100) ||
	    (rdev->family == CHIP_RS200)) {
		tmp = RREG32(RADEON_MEM_CNTL);
		if (tmp & RV100_HALF_MODE) {
			rdev->mc.vram_width = 32;
		} else {
			rdev->mc.vram_width = 64;
		}
		if (rdev->flags & RADEON_SINGLE_CRTC) {
			rdev->mc.vram_width /= 4;
			rdev->mc.vram_is_ddr = true;
		}
	} else if (rdev->family <= CHIP_RV280) {
		tmp = RREG32(RADEON_MEM_CNTL);
		if (tmp & RADEON_MEM_NUM_CHANNELS_MASK) {
			rdev->mc.vram_width = 128;
		} else {
			rdev->mc.vram_width = 64;
		}
	} else {
		/* newer IGPs */
		rdev->mc.vram_width = 128;
	}
}