#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* alloc_anon_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fs_cnt ; 
 TYPE_1__* drm_fs_mnt ; 
 int /*<<< orphan*/  drm_fs_type ; 
 int simple_pin_fs (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (TYPE_1__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *drm_fs_inode_new(void)
{
	struct inode *inode;
	int r;

	r = simple_pin_fs(&drm_fs_type, &drm_fs_mnt, &drm_fs_cnt);
	if (r < 0) {
		DRM_ERROR("Cannot mount pseudo fs: %d\n", r);
		return ERR_PTR(r);
	}

	inode = alloc_anon_inode(drm_fs_mnt->mnt_sb);
	if (IS_ERR(inode))
		simple_release_fs(&drm_fs_mnt, &drm_fs_cnt);

	return inode;
}