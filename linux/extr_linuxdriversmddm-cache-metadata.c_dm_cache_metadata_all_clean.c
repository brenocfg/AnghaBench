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
struct dm_cache_metadata {int /*<<< orphan*/  cache_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 
 int blocks_are_unmapped_or_clean (struct dm_cache_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int dm_cache_metadata_all_clean(struct dm_cache_metadata *cmd, bool *result)
{
	int r;

	READ_LOCK(cmd);
	r = blocks_are_unmapped_or_clean(cmd, 0, cmd->cache_blocks, result);
	READ_UNLOCK(cmd);

	return r;
}