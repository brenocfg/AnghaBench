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
struct sdma_rht_map_elem {int ctr; int /*<<< orphan*/ * sde; } ;

/* Variables and functions */
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static void sdma_populate_sde_map(struct sdma_rht_map_elem *map)
{
	int i;

	for (i = 0; i < roundup_pow_of_two(map->ctr ? : 1) - map->ctr; i++)
		map->sde[map->ctr + i] = map->sde[i];
}