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
struct cache_stat_collector {int /*<<< orphan*/  cache_bypass_misses; int /*<<< orphan*/  cache_bypass_hits; int /*<<< orphan*/  cache_misses; int /*<<< orphan*/  cache_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mark_cache_stats(struct cache_stat_collector *stats,
			     bool hit, bool bypass)
{
	if (!bypass)
		if (hit)
			atomic_inc(&stats->cache_hits);
		else
			atomic_inc(&stats->cache_misses);
	else
		if (hit)
			atomic_inc(&stats->cache_bypass_hits);
		else
			atomic_inc(&stats->cache_bypass_misses);
}