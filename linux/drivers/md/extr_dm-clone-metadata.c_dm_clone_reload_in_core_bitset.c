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
struct dm_clone_metadata {int /*<<< orphan*/  lock; scalar_t__ fail_io; } ;

/* Variables and functions */
 int EINVAL ; 
 int __load_bitset_in_core (struct dm_clone_metadata*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_clone_reload_in_core_bitset(struct dm_clone_metadata *cmd)
{
	int r = -EINVAL;

	down_write(&cmd->lock);

	if (cmd->fail_io)
		goto out;

	r = __load_bitset_in_core(cmd);
out:
	up_write(&cmd->lock);

	return r;
}