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
struct csio_hw {scalar_t__ debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (scalar_t__) ; 

__attribute__((used)) static int
csio_dfs_destroy(struct csio_hw *hw)
{
	if (hw->debugfs_root)
		debugfs_remove_recursive(hw->debugfs_root);

	return 0;
}