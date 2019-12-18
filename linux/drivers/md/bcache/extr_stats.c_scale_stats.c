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
struct cache_stats {unsigned long rescale; int /*<<< orphan*/  sectors_bypassed; int /*<<< orphan*/  cache_miss_collisions; int /*<<< orphan*/  cache_readaheads; int /*<<< orphan*/  cache_bypass_misses; int /*<<< orphan*/  cache_bypass_hits; int /*<<< orphan*/  cache_misses; int /*<<< orphan*/  cache_hits; } ;

/* Variables and functions */
 int /*<<< orphan*/  scale_stat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scale_stats(struct cache_stats *stats, unsigned long rescale_at)
{
	if (++stats->rescale == rescale_at) {
		stats->rescale = 0;
		scale_stat(&stats->cache_hits);
		scale_stat(&stats->cache_misses);
		scale_stat(&stats->cache_bypass_hits);
		scale_stat(&stats->cache_bypass_misses);
		scale_stat(&stats->cache_readaheads);
		scale_stat(&stats->cache_miss_collisions);
		scale_stat(&stats->sectors_bypassed);
	}
}