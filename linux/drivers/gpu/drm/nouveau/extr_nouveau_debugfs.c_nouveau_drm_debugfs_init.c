#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
struct nouveau_drm {TYPE_1__ vbios; } ;
struct drm_minor {int /*<<< orphan*/  debugfs_root; int /*<<< orphan*/  dev; } ;
struct dentry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  fops; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NOUVEAU_DEBUGFS_ENTRIES ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 TYPE_3__* d_inode (struct dentry*) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 TYPE_2__* nouveau_debugfs_files ; 
 int /*<<< orphan*/  nouveau_debugfs_list ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

int
nouveau_drm_debugfs_init(struct drm_minor *minor)
{
	struct nouveau_drm *drm = nouveau_drm(minor->dev);
	struct dentry *dentry;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(nouveau_debugfs_files); i++) {
		dentry = debugfs_create_file(nouveau_debugfs_files[i].name,
					     S_IRUGO | S_IWUSR,
					     minor->debugfs_root, minor->dev,
					     nouveau_debugfs_files[i].fops);
		if (!dentry)
			return -ENOMEM;
	}

	ret = drm_debugfs_create_files(nouveau_debugfs_list,
				       NOUVEAU_DEBUGFS_ENTRIES,
				       minor->debugfs_root, minor);
	if (ret)
		return ret;

	/* Set the size of the vbios since we know it, and it's confusing to
	 * userspace if it wants to seek() but the file has a length of 0
	 */
	dentry = debugfs_lookup("vbios.rom", minor->debugfs_root);
	if (!dentry)
		return 0;

	d_inode(dentry)->i_size = drm->vbios.length;
	dput(dentry);

	return 0;
}