#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int num_placement; int /*<<< orphan*/  num_busy_placement; } ;
struct radeon_bo {TYPE_2__ placement; TYPE_1__* placements; } ;
struct TYPE_3__ {int fpfn; int lpfn; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ RADEON_GEM_DOMAIN_VRAM ; 

void radeon_uvd_force_into_uvd_segment(struct radeon_bo *rbo,
				       uint32_t allowed_domains)
{
	int i;

	for (i = 0; i < rbo->placement.num_placement; ++i) {
		rbo->placements[i].fpfn = 0 >> PAGE_SHIFT;
		rbo->placements[i].lpfn = (256 * 1024 * 1024) >> PAGE_SHIFT;
	}

	/* If it must be in VRAM it must be in the first segment as well */
	if (allowed_domains == RADEON_GEM_DOMAIN_VRAM)
		return;

	/* abort if we already have more than one placement */
	if (rbo->placement.num_placement > 1)
		return;

	/* add another 256MB segment */
	rbo->placements[1] = rbo->placements[0];
	rbo->placements[1].fpfn += (256 * 1024 * 1024) >> PAGE_SHIFT;
	rbo->placements[1].lpfn += (256 * 1024 * 1024) >> PAGE_SHIFT;
	rbo->placement.num_placement++;
	rbo->placement.num_busy_placement++;
}