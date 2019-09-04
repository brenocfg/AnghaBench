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
struct vfsmount {struct super_block* mnt_sb; } ;
struct super_block {TYPE_2__* s_op; } ;
struct file_system_type {int dummy; } ;
struct TYPE_3__ {struct vfsmount* gemfs; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct TYPE_4__ {int (* remount_fs ) (struct super_block*,int*,char*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 struct file_system_type* get_fs_type (char*) ; 
 scalar_t__ has_transparent_hugepage () ; 
 struct vfsmount* kern_mount (struct file_system_type*) ; 
 int /*<<< orphan*/  kern_unmount (struct vfsmount*) ; 
 int stub1 (struct super_block*,int*,char*) ; 

int i915_gemfs_init(struct drm_i915_private *i915)
{
	struct file_system_type *type;
	struct vfsmount *gemfs;

	type = get_fs_type("tmpfs");
	if (!type)
		return -ENODEV;

	gemfs = kern_mount(type);
	if (IS_ERR(gemfs))
		return PTR_ERR(gemfs);

	/*
	 * Enable huge-pages for objects that are at least HPAGE_PMD_SIZE, most
	 * likely 2M. Note that within_size may overallocate huge-pages, if say
	 * we allocate an object of size 2M + 4K, we may get 2M + 2M, but under
	 * memory pressure shmem should split any huge-pages which can be
	 * shrunk.
	 */

	if (has_transparent_hugepage()) {
		struct super_block *sb = gemfs->mnt_sb;
		/* FIXME: Disabled until we get W/A for read BW issue. */
		char options[] = "huge=never";
		int flags = 0;
		int err;

		err = sb->s_op->remount_fs(sb, &flags, options);
		if (err) {
			kern_unmount(gemfs);
			return err;
		}
	}

	i915->mm.gemfs = gemfs;

	return 0;
}