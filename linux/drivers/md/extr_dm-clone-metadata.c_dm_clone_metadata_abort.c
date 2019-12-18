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
struct dm_clone_metadata {int fail_io; int /*<<< orphan*/  lock; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int EPERM ; 
 int __create_persistent_data_structures (struct dm_clone_metadata*,int) ; 
 int /*<<< orphan*/  __destroy_persistent_data_structures (struct dm_clone_metadata*) ; 
 scalar_t__ dm_bm_is_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_clone_metadata_abort(struct dm_clone_metadata *cmd)
{
	int r = -EPERM;

	down_write(&cmd->lock);

	if (cmd->fail_io || dm_bm_is_read_only(cmd->bm))
		goto out;

	__destroy_persistent_data_structures(cmd);

	r = __create_persistent_data_structures(cmd, false);
	if (r) {
		/* If something went wrong we can neither write nor read the metadata */
		cmd->fail_io = true;
	}
out:
	up_write(&cmd->lock);

	return r;
}