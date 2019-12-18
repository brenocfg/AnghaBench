#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ partname; scalar_t__ partid; struct dentry* dfs_dir; } ;
struct device {int dummy; } ;
struct mtd_info {TYPE_1__ dbg; struct device dev; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,struct dentry*) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct dentry* dfs_dir_mtd ; 
 int /*<<< orphan*/  mtd_partid_debug_fops ; 
 int /*<<< orphan*/  mtd_partname_debug_fops ; 

__attribute__((used)) static void mtd_debugfs_populate(struct mtd_info *mtd)
{
	struct device *dev = &mtd->dev;
	struct dentry *root, *dent;

	if (IS_ERR_OR_NULL(dfs_dir_mtd))
		return;

	root = debugfs_create_dir(dev_name(dev), dfs_dir_mtd);
	if (IS_ERR_OR_NULL(root)) {
		dev_dbg(dev, "won't show data in debugfs\n");
		return;
	}

	mtd->dbg.dfs_dir = root;

	if (mtd->dbg.partid) {
		dent = debugfs_create_file("partid", 0400, root, mtd,
					   &mtd_partid_debug_fops);
		if (IS_ERR_OR_NULL(dent))
			dev_err(dev, "can't create debugfs entry for partid\n");
	}

	if (mtd->dbg.partname) {
		dent = debugfs_create_file("partname", 0400, root, mtd,
					   &mtd_partname_debug_fops);
		if (IS_ERR_OR_NULL(dent))
			dev_err(dev,
				"can't create debugfs entry for partname\n");
	}
}