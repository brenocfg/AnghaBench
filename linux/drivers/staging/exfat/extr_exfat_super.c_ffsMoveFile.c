#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  scalar_t__ u32 ;
struct uni_name_t {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {scalar_t__ vol_type; scalar_t__ root_dir; int cluster_size_bits; int /*<<< orphan*/  v_sem; scalar_t__ dev_ejected; TYPE_2__* fs_func; } ;
struct chain_t {scalar_t__ dir; int size; int /*<<< orphan*/  flags; } ;
struct file_id_t {int entry; scalar_t__ start_clu; int size; int /*<<< orphan*/  flags; struct chain_t dir; } ;
struct dentry_t {int dummy; } ;
struct TYPE_5__ {scalar_t__ name; } ;
struct dentry {struct inode* d_inode; TYPE_1__ d_name; } ;
typedef  int s32 ;
struct TYPE_8__ {struct file_id_t fid; } ;
struct TYPE_7__ {struct fs_info_t fs_info; } ;
struct TYPE_6__ {int (* get_entry_attr ) (struct dentry_t*) ;scalar_t__ (* get_entry_type ) (struct dentry_t*) ;int (* count_ext_entries ) (struct super_block*,struct chain_t*,int,struct dentry_t*) ;int /*<<< orphan*/  (* delete_dir_entry ) (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ATTR_READONLY ; 
 scalar_t__ EXFAT ; 
 TYPE_4__* EXFAT_I (struct inode*) ; 
 TYPE_3__* EXFAT_SB (struct super_block*) ; 
 int FFS_ERROR ; 
 int FFS_FILEEXIST ; 
 int FFS_INVALIDFID ; 
 int FFS_MEDIAERR ; 
 int FFS_PERMISSIONERR ; 
 int FFS_SUCCESS ; 
 scalar_t__ TYPE_DIR ; 
 int /*<<< orphan*/  VOL_CLEAN ; 
 int /*<<< orphan*/  VOL_DIRTY ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_set_vol_flags (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_sync (struct super_block*,int) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_dir_empty (struct super_block*,struct chain_t*) ; 
 int move_file (struct inode*,struct chain_t*,int,struct chain_t*,struct uni_name_t*,struct file_id_t*) ; 
 int rename_file (struct inode*,struct chain_t*,int,struct uni_name_t*,struct file_id_t*) ; 
 int resolve_path (struct inode*,char*,struct chain_t*,struct uni_name_t*) ; 
 int stub1 (struct dentry_t*) ; 
 scalar_t__ stub2 (struct dentry_t*) ; 
 int stub3 (struct super_block*,struct chain_t*,int,struct dentry_t*) ; 
 int /*<<< orphan*/  stub4 (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_parent_info (struct file_id_t*,struct inode*) ; 

__attribute__((used)) static int ffsMoveFile(struct inode *old_parent_inode, struct file_id_t *fid,
		       struct inode *new_parent_inode, struct dentry *new_dentry)
{
	s32 ret;
	s32 dentry;
	struct chain_t olddir, newdir;
	struct chain_t *p_dir = NULL;
	struct uni_name_t uni_name;
	struct dentry_t *ep;
	struct super_block *sb = old_parent_inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	u8 *new_path = (u8 *)new_dentry->d_name.name;
	struct inode *new_inode = new_dentry->d_inode;
	int num_entries;
	struct file_id_t *new_fid = NULL;
	s32 new_entry = 0;

	/* check the validity of the given file id */
	if (!fid)
		return FFS_INVALIDFID;

	/* check the validity of pointer parameters */
	if (!new_path || (*new_path == '\0'))
		return FFS_ERROR;

	/* acquire the lock for file system critical section */
	down(&p_fs->v_sem);

	update_parent_info(fid, old_parent_inode);

	olddir.dir = fid->dir.dir;
	olddir.size = fid->dir.size;
	olddir.flags = fid->dir.flags;

	dentry = fid->entry;

	/* check if the old file is "." or ".." */
	if (p_fs->vol_type != EXFAT) {
		if ((olddir.dir != p_fs->root_dir) && (dentry < 2)) {
			ret = FFS_PERMISSIONERR;
			goto out2;
		}
	}

	ep = get_entry_in_dir(sb, &olddir, dentry, NULL);
	if (!ep) {
		ret = FFS_MEDIAERR;
		goto out2;
	}

	if (p_fs->fs_func->get_entry_attr(ep) & ATTR_READONLY) {
		ret = FFS_PERMISSIONERR;
		goto out2;
	}

	/* check whether new dir is existing directory and empty */
	if (new_inode) {
		u32 entry_type;

		ret = FFS_MEDIAERR;
		new_fid = &EXFAT_I(new_inode)->fid;

		update_parent_info(new_fid, new_parent_inode);

		p_dir = &(new_fid->dir);
		new_entry = new_fid->entry;
		ep = get_entry_in_dir(sb, p_dir, new_entry, NULL);
		if (!ep)
			goto out;

		entry_type = p_fs->fs_func->get_entry_type(ep);

		if (entry_type == TYPE_DIR) {
			struct chain_t new_clu;

			new_clu.dir = new_fid->start_clu;
			new_clu.size = (s32)((new_fid->size - 1) >>
					     p_fs->cluster_size_bits) + 1;
			new_clu.flags = new_fid->flags;

			if (!is_dir_empty(sb, &new_clu)) {
				ret = FFS_FILEEXIST;
				goto out;
			}
		}
	}

	/* check the validity of directory name in the given new pathname */
	ret = resolve_path(new_parent_inode, new_path, &newdir, &uni_name);
	if (ret)
		goto out2;

	fs_set_vol_flags(sb, VOL_DIRTY);

	if (olddir.dir == newdir.dir)
		ret = rename_file(new_parent_inode, &olddir, dentry, &uni_name,
				  fid);
	else
		ret = move_file(new_parent_inode, &olddir, dentry, &newdir,
				&uni_name, fid);

	if ((ret == FFS_SUCCESS) && new_inode) {
		/* delete entries of new_dir */
		ep = get_entry_in_dir(sb, p_dir, new_entry, NULL);
		if (!ep)
			goto out;

		num_entries = p_fs->fs_func->count_ext_entries(sb, p_dir,
							       new_entry, ep);
		if (num_entries < 0)
			goto out;
		p_fs->fs_func->delete_dir_entry(sb, p_dir, new_entry, 0,
						num_entries + 1);
	}
out:
#ifdef CONFIG_EXFAT_DELAYED_SYNC
	fs_sync(sb, false);
	fs_set_vol_flags(sb, VOL_CLEAN);
#endif

	if (p_fs->dev_ejected)
		ret = FFS_MEDIAERR;
out2:
	/* release the lock for file system critical section */
	up(&p_fs->v_sem);

	return ret;
}