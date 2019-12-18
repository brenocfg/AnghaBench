#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtdswap_dev {int /*<<< orphan*/  dev; TYPE_2__* mtd; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {struct dentry* dfs_dir; } ;
struct TYPE_4__ {TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  S_IRUSR ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct mtdswap_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtdswap_fops ; 

__attribute__((used)) static int mtdswap_add_debugfs(struct mtdswap_dev *d)
{
	struct dentry *root = d->mtd->dbg.dfs_dir;
	struct dentry *dent;

	if (!IS_ENABLED(CONFIG_DEBUG_FS))
		return 0;

	if (IS_ERR_OR_NULL(root))
		return -1;

	dent = debugfs_create_file("mtdswap_stats", S_IRUSR, root, d,
				&mtdswap_fops);
	if (!dent) {
		dev_err(d->dev, "debugfs_create_file failed\n");
		return -1;
	}

	return 0;
}