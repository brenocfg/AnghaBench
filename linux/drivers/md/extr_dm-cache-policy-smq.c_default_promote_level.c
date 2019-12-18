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
struct TYPE_2__ {unsigned int hits; unsigned int misses; } ;
struct smq_policy {TYPE_1__ cache_stats; } ;

/* Variables and functions */
 unsigned int safe_div (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned default_promote_level(struct smq_policy *mq)
{
	/*
	 * The promote level depends on the current performance of the
	 * cache.
	 *
	 * If the cache is performing badly, then we can't afford
	 * to promote much without causing performance to drop below that
	 * of the origin device.
	 *
	 * If the cache is performing well, then we don't need to promote
	 * much.  If it isn't broken, don't fix it.
	 *
	 * If the cache is middling then we promote more.
	 *
	 * This scheme reminds me of a graph of entropy vs probability of a
	 * binary variable.
	 */
	static unsigned table[] = {1, 1, 1, 2, 4, 6, 7, 8, 7, 6, 4, 4, 3, 3, 2, 2, 1};

	unsigned hits = mq->cache_stats.hits;
	unsigned misses = mq->cache_stats.misses;
	unsigned index = safe_div(hits << 4u, hits + misses);
	return table[index];
}