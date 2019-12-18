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
struct csio_hw {int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  csio_mem_debugfs_fops ; 
 int /*<<< orphan*/  debugfs_create_file_size (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,unsigned int) ; 

void csio_add_debugfs_mem(struct csio_hw *hw, const char *name,
				 unsigned int idx, unsigned int size_mb)
{
	debugfs_create_file_size(name, S_IRUSR, hw->debugfs_root,
				 (void *)hw + idx, &csio_mem_debugfs_fops,
				 size_mb << 20);
}