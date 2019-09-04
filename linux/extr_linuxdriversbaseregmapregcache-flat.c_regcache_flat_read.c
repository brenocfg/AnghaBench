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
struct regmap {unsigned int* cache; } ;

/* Variables and functions */
 unsigned int regcache_flat_get_index (struct regmap*,unsigned int) ; 

__attribute__((used)) static int regcache_flat_read(struct regmap *map,
			      unsigned int reg, unsigned int *value)
{
	unsigned int *cache = map->cache;
	unsigned int index = regcache_flat_get_index(map, reg);

	*value = cache[index];

	return 0;
}