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
struct vfsmount {int dummy; } ;
struct file_system_type {int dummy; } ;
struct TYPE_2__ {struct vfsmount* gemfs; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 struct file_system_type* get_fs_type (char*) ; 
 struct vfsmount* kern_mount (struct file_system_type*) ; 

int i915_gemfs_init(struct drm_i915_private *i915)
{
	struct file_system_type *type;
	struct vfsmount *gemfs;

	type = get_fs_type("tmpfs");
	if (!type)
		return -ENODEV;

	/*
	 * By creating our own shmemfs mountpoint, we can pass in
	 * mount flags that better match our usecase.
	 *
	 * One example, although it is probably better with a per-file
	 * control, is selecting huge page allocations ("huge=within_size").
	 * Currently unused due to bandwidth issues (slow reads) on Broadwell+.
	 */

	gemfs = kern_mount(type);
	if (IS_ERR(gemfs))
		return PTR_ERR(gemfs);

	i915->mm.gemfs = gemfs;

	return 0;
}