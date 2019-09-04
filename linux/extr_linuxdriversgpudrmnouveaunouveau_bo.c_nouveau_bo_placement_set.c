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
typedef  int uint32_t ;
struct ttm_placement {int /*<<< orphan*/  num_busy_placement; int /*<<< orphan*/  busy_placement; int /*<<< orphan*/  num_placement; int /*<<< orphan*/  placement; } ;
struct nouveau_bo {int /*<<< orphan*/  busy_placements; int /*<<< orphan*/  placements; scalar_t__ pin_refcnt; scalar_t__ force_coherent; struct ttm_placement placement; } ;

/* Variables and functions */
 int TTM_PL_FLAG_NO_EVICT ; 
 int TTM_PL_FLAG_UNCACHED ; 
 int TTM_PL_MASK_CACHING ; 
 int /*<<< orphan*/  set_placement_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_placement_range (struct nouveau_bo*,int) ; 

void
nouveau_bo_placement_set(struct nouveau_bo *nvbo, uint32_t type, uint32_t busy)
{
	struct ttm_placement *pl = &nvbo->placement;
	uint32_t flags = (nvbo->force_coherent ? TTM_PL_FLAG_UNCACHED :
						 TTM_PL_MASK_CACHING) |
			 (nvbo->pin_refcnt ? TTM_PL_FLAG_NO_EVICT : 0);

	pl->placement = nvbo->placements;
	set_placement_list(nvbo->placements, &pl->num_placement,
			   type, flags);

	pl->busy_placement = nvbo->busy_placements;
	set_placement_list(nvbo->busy_placements, &pl->num_busy_placement,
			   type | busy, flags);

	set_placement_range(nvbo, type);
}