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
struct bochs_bo {struct ttm_placement placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 struct bochs_bo* bochs_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  bochs_ttm_bo_is_bochs_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  bochs_ttm_placement (struct bochs_bo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bochs_bo_evict_flags(struct ttm_buffer_object *bo, struct ttm_placement *pl)
{
	struct bochs_bo *bochsbo = bochs_bo(bo);

	if (!bochs_ttm_bo_is_bochs_bo(bo))
		return;

	bochs_ttm_placement(bochsbo, TTM_PL_FLAG_SYSTEM);
	*pl = bochsbo->placement;
}