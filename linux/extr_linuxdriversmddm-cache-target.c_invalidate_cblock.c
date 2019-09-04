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
struct cache {int /*<<< orphan*/  cmd; int /*<<< orphan*/  policy; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ) ; 
 int ENODATA ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int dm_cache_remove_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,int) ; 
 int policy_invalidate_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int invalidate_cblock(struct cache *cache, dm_cblock_t cblock)
{
	int r = policy_invalidate_mapping(cache->policy, cblock);
	if (!r) {
		r = dm_cache_remove_mapping(cache->cmd, cblock);
		if (r) {
			DMERR_LIMIT("%s: invalidation failed; couldn't update on disk metadata",
				    cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_remove_mapping", r);
		}

	} else if (r == -ENODATA) {
		/*
		 * Harmless, already unmapped.
		 */
		r = 0;

	} else
		DMERR("%s: policy_invalidate_mapping failed", cache_device_name(cache));

	return r;
}