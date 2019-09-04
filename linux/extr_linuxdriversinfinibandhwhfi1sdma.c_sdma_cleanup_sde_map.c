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
struct sdma_rht_map_elem {unsigned int ctr; unsigned int mask; struct sdma_engine** sde; } ;
struct sdma_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (struct sdma_engine**,struct sdma_engine**,unsigned int) ; 
 unsigned int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  sdma_populate_sde_map (struct sdma_rht_map_elem*) ; 

__attribute__((used)) static void sdma_cleanup_sde_map(struct sdma_rht_map_elem *map,
				 struct sdma_engine *sde)
{
	unsigned int i, pow;

	/* only need to check the first ctr entries for a match */
	for (i = 0; i < map->ctr; i++) {
		if (map->sde[i] == sde) {
			memmove(&map->sde[i], &map->sde[i + 1],
				(map->ctr - i - 1) * sizeof(map->sde[0]));
			map->ctr--;
			pow = roundup_pow_of_two(map->ctr ? : 1);
			map->mask = pow - 1;
			sdma_populate_sde_map(map);
			break;
		}
	}
}