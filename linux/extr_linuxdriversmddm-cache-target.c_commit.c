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
struct TYPE_2__ {int /*<<< orphan*/  commit_count; } ;
struct cache {int /*<<< orphan*/  cmd; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int dm_cache_commit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,int) ; 

__attribute__((used)) static int commit(struct cache *cache, bool clean_shutdown)
{
	int r;

	if (get_cache_mode(cache) >= CM_READ_ONLY)
		return -EINVAL;

	atomic_inc(&cache->stats.commit_count);
	r = dm_cache_commit(cache->cmd, clean_shutdown);
	if (r)
		metadata_operation_failed(cache, "dm_cache_commit", r);

	return r;
}