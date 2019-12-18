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
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 

int dm_cache_size(struct dm_cache_metadata *cmd, dm_cblock_t *result)
{
	READ_LOCK(cmd);
	*result = cmd->cache_blocks;
	READ_UNLOCK(cmd);

	return 0;
}