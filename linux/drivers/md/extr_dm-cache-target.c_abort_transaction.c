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
struct cache {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_FAIL ; 
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  DMERR (char*,char const*) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,char const*) ; 
 char* cache_device_name (struct cache*) ; 
 scalar_t__ dm_cache_metadata_abort (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_cache_metadata_set_needs_check (int /*<<< orphan*/ ) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 
 int /*<<< orphan*/  set_cache_mode (struct cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abort_transaction(struct cache *cache)
{
	const char *dev_name = cache_device_name(cache);

	if (get_cache_mode(cache) >= CM_READ_ONLY)
		return;

	if (dm_cache_metadata_set_needs_check(cache->cmd)) {
		DMERR("%s: failed to set 'needs_check' flag in metadata", dev_name);
		set_cache_mode(cache, CM_FAIL);
	}

	DMERR_LIMIT("%s: aborting current metadata transaction", dev_name);
	if (dm_cache_metadata_abort(cache->cmd)) {
		DMERR("%s: failed to abort metadata transaction", dev_name);
		set_cache_mode(cache, CM_FAIL);
	}
}