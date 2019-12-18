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

/* Variables and functions */
 char* DRV_NAME ; 
 int /*<<< orphan*/  S_IRUGO ; 
 void* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debugfs_root ; 
 void* flows_dentry ; 
 int /*<<< orphan*/  usnic_debugfs_buildinfo_ops ; 

void usnic_debugfs_init(void)
{
	debugfs_root = debugfs_create_dir(DRV_NAME, NULL);

	flows_dentry = debugfs_create_dir("flows", debugfs_root);

	debugfs_create_file("build-info", S_IRUGO, debugfs_root,
				NULL, &usnic_debugfs_buildinfo_ops);
}