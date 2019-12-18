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
struct dm_cache_metadata {int fail_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int __create_persistent_data_objects (struct dm_cache_metadata*,int) ; 
 int /*<<< orphan*/  __destroy_persistent_data_objects (struct dm_cache_metadata*) ; 

int dm_cache_metadata_abort(struct dm_cache_metadata *cmd)
{
	int r;

	WRITE_LOCK(cmd);
	__destroy_persistent_data_objects(cmd);
	r = __create_persistent_data_objects(cmd, false);
	if (r)
		cmd->fail_io = true;
	WRITE_UNLOCK(cmd);

	return r;
}