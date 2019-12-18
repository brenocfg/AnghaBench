#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {int cluster_size_bits; scalar_t__ vol_type; int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; TYPE_2__* fs_func; } ;
struct TYPE_4__ {int flags; scalar_t__ size; int /*<<< orphan*/  dir; } ;
struct file_id_t {int size; int flags; int /*<<< orphan*/  start_clu; scalar_t__ entry; TYPE_1__ dir; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int flags; scalar_t__ size; int /*<<< orphan*/  dir; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {struct fs_info_t fs_info; } ;
struct TYPE_5__ {int (* get_entry_attr ) (struct dentry_t*) ;int /*<<< orphan*/  (* free_cluster ) (struct super_block*,struct chain_t*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ATTR_READONLY ; 
 int /*<<< orphan*/  CLUSTER_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ EXFAT ; 
 TYPE_3__* EXFAT_SB (struct super_block*) ; 
 int FFS_INVALIDFID ; 
 int FFS_MEDIAERR ; 
 int FFS_PERMISSIONERR ; 
 int FFS_SUCCESS ; 
 int /*<<< orphan*/  VOL_CLEAN ; 
 int /*<<< orphan*/  VOL_DIRTY ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_set_vol_flags (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_sync (struct super_block*,int) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_file (struct inode*,struct chain_t*,scalar_t__) ; 
 int stub1 (struct dentry_t*) ; 
 int /*<<< orphan*/  stub2 (struct super_block*,struct chain_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffsRemoveFile(struct inode *inode, struct file_id_t *fid)
{
	s32 dentry;
	int ret = FFS_SUCCESS;
	struct chain_t dir, clu_to_free;
	struct dentry_t *ep;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	/* check the validity of the given file id */
	if (!fid)
		return FFS_INVALIDFID;

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	dir.dir = fid->dir.dir;
	dir.size = fid->dir.size;
	dir.flags = fid->dir.flags;

	dentry = fid->entry;

	ep = get_entry_in_dir(sb, &dir, dentry, NULL);
	if (!ep) {
		ret = FFS_MEDIAERR;
		goto out;
	}

	if (p_fs->fs_func->get_entry_attr(ep) & ATTR_READONLY) {
		ret = FFS_PERMISSIONERR;
		goto out;
	}
	fs_set_vol_flags(sb, VOL_DIRTY);

	/* (1) update the directory entry */
	remove_file(inode, &dir, dentry);

	clu_to_free.dir = fid->start_clu;
	clu_to_free.size = (s32)((fid->size - 1) >> p_fs->cluster_size_bits) + 1;
	clu_to_free.flags = fid->flags;

	/* (2) free the clusters */
	p_fs->fs_func->free_cluster(sb, &clu_to_free, 0);

	fid->size = 0;
	fid->start_clu = CLUSTER_32(~0);
	fid->flags = (p_fs->vol_type == EXFAT) ? 0x03 : 0x01;

#ifdef CONFIG_EXFAT_DELAYED_SYNC
	fs_sync(sb, false);
	fs_set_vol_flags(sb, VOL_CLEAN);
#endif

	if (p_fs->dev_ejected)
		ret = FFS_MEDIAERR;
out:
	/* release the lock for file system critical section */
	up(&p_fs->v_sem);

	return ret;
}