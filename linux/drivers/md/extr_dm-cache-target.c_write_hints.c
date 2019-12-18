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
struct cache {int /*<<< orphan*/  policy; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int EINVAL ; 
 int dm_cache_write_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,int) ; 

__attribute__((used)) static int write_hints(struct cache *cache)
{
	int r;

	if (get_cache_mode(cache) >= CM_READ_ONLY)
		return -EINVAL;

	r = dm_cache_write_hints(cache->cmd, cache->policy);
	if (r) {
		metadata_operation_failed(cache, "dm_cache_write_hints", r);
		return r;
	}

	return 0;
}