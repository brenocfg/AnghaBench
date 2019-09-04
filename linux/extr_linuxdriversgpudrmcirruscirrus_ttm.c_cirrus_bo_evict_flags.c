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
struct cirrus_bo {struct ttm_placement placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 struct cirrus_bo* cirrus_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  cirrus_ttm_bo_is_cirrus_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  cirrus_ttm_placement (struct cirrus_bo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cirrus_bo_evict_flags(struct ttm_buffer_object *bo, struct ttm_placement *pl)
{
	struct cirrus_bo *cirrusbo = cirrus_bo(bo);

	if (!cirrus_ttm_bo_is_cirrus_bo(bo))
		return;

	cirrus_ttm_placement(cirrusbo, TTM_PL_FLAG_SYSTEM);
	*pl = cirrusbo->placement;
}