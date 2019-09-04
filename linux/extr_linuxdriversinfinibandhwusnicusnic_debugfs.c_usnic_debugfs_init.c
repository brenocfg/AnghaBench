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
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 void* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debugfs_root ; 
 void* flows_dentry ; 
 int /*<<< orphan*/  usnic_debugfs_buildinfo_ops ; 
 int /*<<< orphan*/  usnic_err (char*,...) ; 

void usnic_debugfs_init(void)
{
	debugfs_root = debugfs_create_dir(DRV_NAME, NULL);
	if (IS_ERR(debugfs_root)) {
		usnic_err("Failed to create debugfs root dir, check if debugfs is enabled in kernel configuration\n");
		goto out_clear_root;
	}

	flows_dentry = debugfs_create_dir("flows", debugfs_root);
	if (IS_ERR_OR_NULL(flows_dentry)) {
		usnic_err("Failed to create debugfs flow dir with err %ld\n",
				PTR_ERR(flows_dentry));
		goto out_free_root;
	}

	debugfs_create_file("build-info", S_IRUGO, debugfs_root,
				NULL, &usnic_debugfs_buildinfo_ops);
	return;

out_free_root:
	debugfs_remove_recursive(debugfs_root);
out_clear_root:
	debugfs_root = NULL;
}