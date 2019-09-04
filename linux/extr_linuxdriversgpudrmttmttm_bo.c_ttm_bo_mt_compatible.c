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
struct ttm_place {int flags; } ;
struct ttm_mem_type_manager {int available_caching; } ;

/* Variables and functions */
 int TTM_PL_MASK_MEM ; 
 int ttm_bo_type_flags (int) ; 

__attribute__((used)) static bool ttm_bo_mt_compatible(struct ttm_mem_type_manager *man,
				 uint32_t mem_type,
				 const struct ttm_place *place,
				 uint32_t *masked_placement)
{
	uint32_t cur_flags = ttm_bo_type_flags(mem_type);

	if ((cur_flags & place->flags & TTM_PL_MASK_MEM) == 0)
		return false;

	if ((place->flags & man->available_caching) == 0)
		return false;

	cur_flags |= (place->flags & man->available_caching);

	*masked_placement = cur_flags;
	return true;
}