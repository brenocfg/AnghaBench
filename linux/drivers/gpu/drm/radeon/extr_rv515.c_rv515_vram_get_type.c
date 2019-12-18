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
struct TYPE_2__ {int vram_width; int vram_is_ddr; } ;
struct radeon_device {TYPE_1__ mc; } ;

/* Variables and functions */
 int MEM_NUM_CHANNELS_MASK ; 
 int RREG32_MC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RV515_MC_CNTL ; 

__attribute__((used)) static void rv515_vram_get_type(struct radeon_device *rdev)
{
	uint32_t tmp;

	rdev->mc.vram_width = 128;
	rdev->mc.vram_is_ddr = true;
	tmp = RREG32_MC(RV515_MC_CNTL) & MEM_NUM_CHANNELS_MASK;
	switch (tmp) {
	case 0:
		rdev->mc.vram_width = 64;
		break;
	case 1:
		rdev->mc.vram_width = 128;
		break;
	default:
		rdev->mc.vram_width = 128;
		break;
	}
}