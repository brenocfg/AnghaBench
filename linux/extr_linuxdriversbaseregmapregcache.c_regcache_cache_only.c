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
struct regmap {int cache_only; int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;scalar_t__ cache_bypass; int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_regmap_cache_only (struct regmap*,int) ; 

void regcache_cache_only(struct regmap *map, bool enable)
{
	map->lock(map->lock_arg);
	WARN_ON(map->cache_bypass && enable);
	map->cache_only = enable;
	trace_regmap_cache_only(map, enable);
	map->unlock(map->lock_arg);
}