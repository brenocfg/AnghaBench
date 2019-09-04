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
struct ttm_placement {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;
struct hibmc_bo {struct ttm_placement placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 struct hibmc_bo* hibmc_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  hibmc_ttm_bo_is_hibmc_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  hibmc_ttm_placement (struct hibmc_bo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hibmc_bo_evict_flags(struct ttm_buffer_object *bo, struct ttm_placement *pl)
{
	struct hibmc_bo *hibmcbo = hibmc_bo(bo);

	if (!hibmc_ttm_bo_is_hibmc_bo(bo))
		return;

	hibmc_ttm_placement(hibmcbo, TTM_PL_FLAG_SYSTEM);
	*pl = hibmcbo->placement;
}