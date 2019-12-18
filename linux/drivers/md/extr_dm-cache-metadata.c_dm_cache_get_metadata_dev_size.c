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
struct dm_cache_metadata {int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  fail_io; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  READ_LOCK (struct dm_cache_metadata*) ; 
 int /*<<< orphan*/  READ_UNLOCK (struct dm_cache_metadata*) ; 
 int dm_sm_get_nr_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dm_cache_get_metadata_dev_size(struct dm_cache_metadata *cmd,
				   dm_block_t *result)
{
	int r = -EINVAL;

	READ_LOCK(cmd);
	if (!cmd->fail_io)
		r = dm_sm_get_nr_blocks(cmd->metadata_sm, result);
	READ_UNLOCK(cmd);

	return r;
}