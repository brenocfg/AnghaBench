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
struct dm_clone_metadata {int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; int /*<<< orphan*/  fail_io; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int dm_sm_get_nr_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dm_clone_get_metadata_dev_size(struct dm_clone_metadata *cmd,
				   dm_block_t *result)
{
	int r = -EINVAL;

	down_read(&cmd->lock);

	if (!cmd->fail_io)
		r = dm_sm_get_nr_blocks(cmd->sm, result);

	up_read(&cmd->lock);

	return r;
}