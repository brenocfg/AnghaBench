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
struct drm_minor {int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfs_root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMADA_DEBUGFS_ENTRIES ; 
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  armada_debugfs_list ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 int /*<<< orphan*/  fops_reg_r ; 
 int /*<<< orphan*/  fops_reg_w ; 

int armada_drm_debugfs_init(struct drm_minor *minor)
{
	struct dentry *de;
	int ret;

	ret = drm_debugfs_create_files(armada_debugfs_list,
				       ARMADA_DEBUGFS_ENTRIES,
				       minor->debugfs_root, minor);
	if (ret)
		return ret;

	de = debugfs_create_file("reg", S_IFREG | S_IRUSR,
				 minor->debugfs_root, minor->dev, &fops_reg_r);
	if (!de)
		return -ENOMEM;

	de = debugfs_create_file("reg_wr", S_IFREG | S_IWUSR,
				 minor->debugfs_root, minor->dev, &fops_reg_w);
	if (!de)
		return -ENOMEM;

	return 0;
}