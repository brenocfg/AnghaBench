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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_placement {scalar_t__ placement; scalar_t__ num_placement; scalar_t__ busy_placement; scalar_t__ num_busy_placement; } ;
struct ttm_mem_reg {int dummy; } ;

/* Variables and functions */
 scalar_t__ ttm_bo_places_compat (scalar_t__,scalar_t__,struct ttm_mem_reg*,int /*<<< orphan*/ *) ; 

bool ttm_bo_mem_compat(struct ttm_placement *placement,
		       struct ttm_mem_reg *mem,
		       uint32_t *new_flags)
{
	if (ttm_bo_places_compat(placement->placement, placement->num_placement,
				 mem, new_flags))
		return true;

	if ((placement->busy_placement != placement->placement ||
	     placement->num_busy_placement > placement->num_placement) &&
	    ttm_bo_places_compat(placement->busy_placement,
				 placement->num_busy_placement,
				 mem, new_flags))
		return true;

	return false;
}