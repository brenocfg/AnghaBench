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
struct regmap {scalar_t__ cache_type; unsigned int max_register; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  cache_ops; } ;

/* Variables and functions */
 scalar_t__ REGCACHE_NONE ; 
 int regcache_read (struct regmap*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

bool regmap_cached(struct regmap *map, unsigned int reg)
{
	int ret;
	unsigned int val;

	if (map->cache_type == REGCACHE_NONE)
		return false;

	if (!map->cache_ops)
		return false;

	if (map->max_register && reg > map->max_register)
		return false;

	map->lock(map->lock_arg);
	ret = regcache_read(map, reg, &val);
	map->unlock(map->lock_arg);
	if (ret)
		return false;

	return true;
}