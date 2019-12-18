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
struct TYPE_3__ {unsigned int num_placement; unsigned int num_busy_placement; TYPE_2__* busy_placement; TYPE_2__* placement; } ;
struct drm_gem_vram_object {TYPE_2__* placements; TYPE_1__ placement; } ;
struct TYPE_4__ {unsigned long flags; scalar_t__ lpfn; scalar_t__ fpfn; } ;

/* Variables and functions */
 unsigned long TTM_PL_FLAG_SYSTEM ; 
 unsigned long TTM_PL_FLAG_UNCACHED ; 
 unsigned long TTM_PL_FLAG_VRAM ; 
 unsigned long TTM_PL_FLAG_WC ; 
 unsigned long TTM_PL_MASK_CACHING ; 

__attribute__((used)) static void drm_gem_vram_placement(struct drm_gem_vram_object *gbo,
				   unsigned long pl_flag)
{
	unsigned int i;
	unsigned int c = 0;

	gbo->placement.placement = gbo->placements;
	gbo->placement.busy_placement = gbo->placements;

	if (pl_flag & TTM_PL_FLAG_VRAM)
		gbo->placements[c++].flags = TTM_PL_FLAG_WC |
					     TTM_PL_FLAG_UNCACHED |
					     TTM_PL_FLAG_VRAM;

	if (pl_flag & TTM_PL_FLAG_SYSTEM)
		gbo->placements[c++].flags = TTM_PL_MASK_CACHING |
					     TTM_PL_FLAG_SYSTEM;

	if (!c)
		gbo->placements[c++].flags = TTM_PL_MASK_CACHING |
					     TTM_PL_FLAG_SYSTEM;

	gbo->placement.num_placement = c;
	gbo->placement.num_busy_placement = c;

	for (i = 0; i < c; ++i) {
		gbo->placements[i].fpfn = 0;
		gbo->placements[i].lpfn = 0;
	}
}