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
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int dm_cache_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,int) ; 
 int /*<<< orphan*/  set_cache_size (struct cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resize_cache_dev(struct cache *cache, dm_cblock_t new_size)
{
	int r;

	r = dm_cache_resize(cache->cmd, new_size);
	if (r) {
		DMERR("%s: could not resize cache metadata", cache_device_name(cache));
		metadata_operation_failed(cache, "dm_cache_resize", r);
		return r;
	}

	set_cache_size(cache, new_size);

	return 0;
}