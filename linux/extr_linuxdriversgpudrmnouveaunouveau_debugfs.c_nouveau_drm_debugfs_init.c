#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_minor {int /*<<< orphan*/  debugfs_root; int /*<<< orphan*/  dev; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fops; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NOUVEAU_DEBUGFS_ENTRIES ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 TYPE_1__* nouveau_debugfs_files ; 
 int /*<<< orphan*/  nouveau_debugfs_list ; 

int
nouveau_drm_debugfs_init(struct drm_minor *minor)
{
	struct dentry *dentry;
	int i;

	for (i = 0; i < ARRAY_SIZE(nouveau_debugfs_files); i++) {
		dentry = debugfs_create_file(nouveau_debugfs_files[i].name,
					     S_IRUGO | S_IWUSR,
					     minor->debugfs_root, minor->dev,
					     nouveau_debugfs_files[i].fops);
		if (!dentry)
			return -ENOMEM;
	}

	return drm_debugfs_create_files(nouveau_debugfs_list,
					NOUVEAU_DEBUGFS_ENTRIES,
					minor->debugfs_root, minor);
}