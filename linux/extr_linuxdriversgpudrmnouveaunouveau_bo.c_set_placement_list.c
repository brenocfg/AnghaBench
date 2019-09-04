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

/* Variables and functions */
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_TT ; 
 int TTM_PL_FLAG_VRAM ; 

__attribute__((used)) static void
set_placement_list(struct ttm_place *pl, unsigned *n, uint32_t type, uint32_t flags)
{
	*n = 0;

	if (type & TTM_PL_FLAG_VRAM)
		pl[(*n)++].flags = TTM_PL_FLAG_VRAM | flags;
	if (type & TTM_PL_FLAG_TT)
		pl[(*n)++].flags = TTM_PL_FLAG_TT | flags;
	if (type & TTM_PL_FLAG_SYSTEM)
		pl[(*n)++].flags = TTM_PL_FLAG_SYSTEM | flags;
}