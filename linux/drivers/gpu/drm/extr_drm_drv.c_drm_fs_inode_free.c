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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fs_cnt ; 
 int /*<<< orphan*/  drm_fs_mnt ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_fs_inode_free(struct inode *inode)
{
	if (inode) {
		iput(inode);
		simple_release_fs(&drm_fs_mnt, &drm_fs_cnt);
	}
}