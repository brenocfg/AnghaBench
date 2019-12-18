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
struct dm_cache_metadata {int changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 

int dm_cache_changed_this_transaction(struct dm_cache_metadata *cmd)
{
	int r;

	READ_LOCK(cmd);
	r = cmd->changed;
	READ_UNLOCK(cmd);

	return r;
}