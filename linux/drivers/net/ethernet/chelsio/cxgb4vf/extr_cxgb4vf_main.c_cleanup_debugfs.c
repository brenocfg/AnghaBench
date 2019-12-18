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
struct adapter {int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_debugfs(struct adapter *adapter)
{
	BUG_ON(IS_ERR_OR_NULL(adapter->debugfs_root));

	/*
	 * Unlike our sister routine cleanup_proc(), we don't need to remove
	 * individual entries because a call will be made to
	 * debugfs_remove_recursive().  We just need to clean up any ancillary
	 * persistent state.
	 */
	/* nothing to do */
}