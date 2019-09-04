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
struct TYPE_2__ {int /*<<< orphan*/  aper_size; int /*<<< orphan*/  aper_base; int /*<<< orphan*/  vram_mtrr; } ;
struct radeon_device {TYPE_1__ mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_io_free_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ttm_fini (struct radeon_device*) ; 

void radeon_bo_fini(struct radeon_device *rdev)
{
	radeon_ttm_fini(rdev);
	arch_phys_wc_del(rdev->mc.vram_mtrr);
	arch_io_free_memtype_wc(rdev->mc.aper_base, rdev->mc.aper_size);
}