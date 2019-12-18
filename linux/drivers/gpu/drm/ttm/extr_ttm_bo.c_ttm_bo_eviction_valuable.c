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
struct ttm_place {scalar_t__ fpfn; scalar_t__ lpfn; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ size; } ;
struct ttm_buffer_object {TYPE_1__ mem; } ;

/* Variables and functions */

bool ttm_bo_eviction_valuable(struct ttm_buffer_object *bo,
			      const struct ttm_place *place)
{
	/* Don't evict this BO if it's outside of the
	 * requested placement range
	 */
	if (place->fpfn >= (bo->mem.start + bo->mem.size) ||
	    (place->lpfn && place->lpfn <= bo->mem.start))
		return false;

	return true;
}