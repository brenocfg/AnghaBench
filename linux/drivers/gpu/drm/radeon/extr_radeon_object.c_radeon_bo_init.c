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
struct TYPE_2__ {int mc_vram_size; int vram_width; scalar_t__ vram_is_ddr; scalar_t__ aper_size; int /*<<< orphan*/  aper_base; int /*<<< orphan*/  vram_mtrr; } ;
struct radeon_device {TYPE_1__ mc; int /*<<< orphan*/  fastfb_working; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int,char) ; 
 int /*<<< orphan*/  arch_io_reserve_memtype_wc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int radeon_ttm_init (struct radeon_device*) ; 

int radeon_bo_init(struct radeon_device *rdev)
{
	/* reserve PAT memory space to WC for VRAM */
	arch_io_reserve_memtype_wc(rdev->mc.aper_base,
				   rdev->mc.aper_size);

	/* Add an MTRR for the VRAM */
	if (!rdev->fastfb_working) {
		rdev->mc.vram_mtrr = arch_phys_wc_add(rdev->mc.aper_base,
						      rdev->mc.aper_size);
	}
	DRM_INFO("Detected VRAM RAM=%lluM, BAR=%lluM\n",
		rdev->mc.mc_vram_size >> 20,
		(unsigned long long)rdev->mc.aper_size >> 20);
	DRM_INFO("RAM width %dbits %cDR\n",
			rdev->mc.vram_width, rdev->mc.vram_is_ddr ? 'D' : 'S');
	return radeon_ttm_init(rdev);
}