#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int aper_base; scalar_t__ gtt_base_align; } ;
struct radeon_device {int flags; TYPE_1__ mc; } ;

/* Variables and functions */
 int RADEON_IS_AGP ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  RADEON_NB_TOM ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r100_vram_get_type (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_vram_init_sizes (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gtt_location (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vram_location (struct radeon_device*,TYPE_1__*,int) ; 

__attribute__((used)) static void r100_mc_init(struct radeon_device *rdev)
{
	u64 base;

	r100_vram_get_type(rdev);
	r100_vram_init_sizes(rdev);
	base = rdev->mc.aper_base;
	if (rdev->flags & RADEON_IS_IGP)
		base = (RREG32(RADEON_NB_TOM) & 0xffff) << 16;
	radeon_vram_location(rdev, &rdev->mc, base);
	rdev->mc.gtt_base_align = 0;
	if (!(rdev->flags & RADEON_IS_AGP))
		radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
}