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
struct radeon_mc {int mc_vram_size; int real_vram_size; } ;
struct TYPE_2__ {scalar_t__ gtt_base_align; } ;
struct radeon_device {TYPE_1__ mc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  radeon_gtt_location (struct radeon_device*,struct radeon_mc*) ; 
 int /*<<< orphan*/  radeon_vram_location (struct radeon_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void si_vram_gtt_location(struct radeon_device *rdev,
			  struct radeon_mc *mc)
{
	if (mc->mc_vram_size > 0xFFC0000000ULL) {
		/* leave room for at least 1024M GTT */
		dev_warn(rdev->dev, "limiting VRAM\n");
		mc->real_vram_size = 0xFFC0000000ULL;
		mc->mc_vram_size = 0xFFC0000000ULL;
	}
	radeon_vram_location(rdev, &rdev->mc, 0);
	rdev->mc.gtt_base_align = 0;
	radeon_gtt_location(rdev, mc);
}