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
typedef  size_t u32 ;
struct TYPE_3__ {size_t num_placement; size_t num_busy_placement; TYPE_2__* busy_placement; TYPE_2__* placement; } ;
struct hibmc_bo {TYPE_2__* placements; TYPE_1__ placement; } ;
struct TYPE_4__ {int flags; scalar_t__ lpfn; scalar_t__ fpfn; } ;

/* Variables and functions */
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_UNCACHED ; 
 int TTM_PL_FLAG_VRAM ; 
 int TTM_PL_FLAG_WC ; 
 int TTM_PL_MASK_CACHING ; 

void hibmc_ttm_placement(struct hibmc_bo *bo, int domain)
{
	u32 count = 0;
	u32 i;

	bo->placement.placement = bo->placements;
	bo->placement.busy_placement = bo->placements;
	if (domain & TTM_PL_FLAG_VRAM)
		bo->placements[count++].flags = TTM_PL_FLAG_WC |
			TTM_PL_FLAG_UNCACHED | TTM_PL_FLAG_VRAM;
	if (domain & TTM_PL_FLAG_SYSTEM)
		bo->placements[count++].flags = TTM_PL_MASK_CACHING |
			TTM_PL_FLAG_SYSTEM;
	if (!count)
		bo->placements[count++].flags = TTM_PL_MASK_CACHING |
			TTM_PL_FLAG_SYSTEM;

	bo->placement.num_placement = count;
	bo->placement.num_busy_placement = count;
	for (i = 0; i < count; i++) {
		bo->placements[i].fpfn = 0;
		bo->placements[i].lpfn = 0;
	}
}