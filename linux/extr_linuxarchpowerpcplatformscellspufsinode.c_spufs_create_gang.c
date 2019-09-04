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
typedef  int umode_t ;
struct vfsmount {int dummy; } ;
struct path {struct dentry* dentry; struct vfsmount* mnt; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int simple_rmdir (struct inode*,struct dentry*) ; 
 int spufs_gang_open (struct path*) ; 
 int spufs_mkgang (struct inode*,struct dentry*,int) ; 

__attribute__((used)) static int spufs_create_gang(struct inode *inode,
			struct dentry *dentry,
			struct vfsmount *mnt, umode_t mode)
{
	struct path path = {.mnt = mnt, .dentry = dentry};
	int ret;

	ret = spufs_mkgang(inode, dentry, mode & 0777);
	if (!ret) {
		ret = spufs_gang_open(&path);
		if (ret < 0) {
			int err = simple_rmdir(inode, dentry);
			WARN_ON(err);
		}
	}
	return ret;
}