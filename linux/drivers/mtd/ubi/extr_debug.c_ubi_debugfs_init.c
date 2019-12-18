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
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ dfs_rootdir ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int ubi_debugfs_init(void)
{
	if (!IS_ENABLED(CONFIG_DEBUG_FS))
		return 0;

	dfs_rootdir = debugfs_create_dir("ubi", NULL);
	if (IS_ERR_OR_NULL(dfs_rootdir)) {
		int err = dfs_rootdir ? PTR_ERR(dfs_rootdir) : -ENODEV;

		pr_err("UBI error: cannot create \"ubi\" debugfs directory, error %d\n",
		       err);
		return err;
	}

	return 0;
}