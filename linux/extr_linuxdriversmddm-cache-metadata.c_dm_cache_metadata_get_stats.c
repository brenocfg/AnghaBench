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
struct dm_cache_statistics {int dummy; } ;
struct dm_cache_metadata {struct dm_cache_statistics stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_LOCK_VOID (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 

void dm_cache_metadata_get_stats(struct dm_cache_metadata *cmd,
				 struct dm_cache_statistics *stats)
{
	READ_LOCK_VOID(cmd);
	*stats = cmd->stats;
	READ_UNLOCK(cmd);
}