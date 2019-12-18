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
struct cblock_range {scalar_t__ begin; scalar_t__ end; } ;
struct cache {int commit_requested; } ;

/* Variables and functions */
 scalar_t__ cblock_succ (scalar_t__) ; 
 int invalidate_cblock (struct cache*,scalar_t__) ; 

__attribute__((used)) static int request_invalidation(struct cache *cache, struct cblock_range *range)
{
	int r = 0;

	/*
	 * We don't need to do any locking here because we know we're in
	 * passthrough mode.  There's is potential for a race between an
	 * invalidation triggered by an io and an invalidation message.  This
	 * is harmless, we must not worry if the policy call fails.
	 */
	while (range->begin != range->end) {
		r = invalidate_cblock(cache, range->begin);
		if (r)
			return r;

		range->begin = cblock_succ(range->begin);
	}

	cache->commit_requested = true;
	return r;
}