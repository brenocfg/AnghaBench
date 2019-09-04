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
struct dm_cache_metadata {int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_LOCK_VOID (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  WRITE_UNLOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  dm_bm_set_read_only (int /*<<< orphan*/ ) ; 

void dm_cache_metadata_set_read_only(struct dm_cache_metadata *cmd)
{
	WRITE_LOCK_VOID(cmd);
	dm_bm_set_read_only(cmd->bm);
	WRITE_UNLOCK(cmd);
}