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
typedef  int u64 ;
struct hw_reg_map {int regblk; int mask; int num_ranges; TYPE_1__* range; } ;
struct TYPE_2__ {int start; int end; } ;

/* Variables and functions */
 int NIX_TXSCH_LVL_CNT ; 
 int TXSCHQ_HWREGMAP ; 
 struct hw_reg_map* txsch_reg_map ; 

bool rvu_check_valid_reg(int regmap, int regblk, u64 reg)
{
	int idx;
	struct hw_reg_map *map;

	/* Only 64bit offsets */
	if (reg & 0x07)
		return false;

	if (regmap == TXSCHQ_HWREGMAP) {
		if (regblk >= NIX_TXSCH_LVL_CNT)
			return false;
		map = &txsch_reg_map[regblk];
	} else {
		return false;
	}

	/* Should never happen */
	if (map->regblk != regblk)
		return false;

	reg &= map->mask;

	for (idx = 0; idx < map->num_ranges; idx++) {
		if (reg >= map->range[idx].start &&
		    reg < map->range[idx].end)
			return true;
	}
	return false;
}