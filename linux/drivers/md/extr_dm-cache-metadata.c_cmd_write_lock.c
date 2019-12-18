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
struct dm_cache_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  bm; scalar_t__ fail_io; } ;

/* Variables and functions */
 scalar_t__ dm_bm_is_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cmd_write_lock(struct dm_cache_metadata *cmd)
{
	down_write(&cmd->root_lock);
	if (cmd->fail_io || dm_bm_is_read_only(cmd->bm)) {
		up_write(&cmd->root_lock);
		return false;
	}
	return true;
}