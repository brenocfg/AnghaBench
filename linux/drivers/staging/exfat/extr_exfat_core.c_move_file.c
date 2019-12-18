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
struct uni_name_t {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {scalar_t__ vol_type; scalar_t__ root_dir; struct fs_func* fs_func; } ;
struct fs_func {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;scalar_t__ (* get_entry_clu0 ) (struct dentry_t*) ;scalar_t__ (* count_ext_entries ) (struct super_block*,struct chain_t*,scalar_t__,struct dentry_t*) ;int (* get_entry_attr ) (struct dentry_t*) ;scalar_t__ (* init_ext_entry ) (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,struct uni_name_t*,struct dos_name_t*) ;int /*<<< orphan*/  (* delete_dir_entry ) (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* set_entry_clu0 ) (struct dentry_t*,scalar_t__) ;int /*<<< orphan*/  (* set_entry_attr ) (struct dentry_t*,int) ;} ;
struct TYPE_3__ {scalar_t__ dir; int flags; int /*<<< orphan*/  size; } ;
struct file_id_t {int attr; scalar_t__ entry; TYPE_1__ dir; } ;
struct dos_name_t {int dummy; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; int flags; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 int ATTR_ARCHIVE ; 
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DENTRY_SIZE ; 
 scalar_t__ EXFAT ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FFS_FULL ; 
 scalar_t__ FFS_INVALIDPATH ; 
 scalar_t__ FFS_MEDIAERR ; 
 scalar_t__ FFS_SUCCESS ; 
 scalar_t__ TYPE_DIR ; 
 scalar_t__ TYPE_FILE ; 
 int /*<<< orphan*/  buf_lock (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_modify (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_unlock (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_empty_entry (struct inode*,struct chain_t*,scalar_t__) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_num_entries_and_dos_name (struct super_block*,struct chain_t*,struct uni_name_t*,scalar_t__*,struct dos_name_t*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 
 int /*<<< orphan*/  stub10 (struct dentry_t*,scalar_t__) ; 
 scalar_t__ stub11 (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,struct uni_name_t*,struct dos_name_t*) ; 
 int /*<<< orphan*/  stub12 (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub2 (struct dentry_t*) ; 
 scalar_t__ stub3 (struct super_block*,struct chain_t*,scalar_t__,struct dentry_t*) ; 
 scalar_t__ stub4 (struct dentry_t*) ; 
 int /*<<< orphan*/  stub5 (struct dentry_t*,int) ; 
 int stub6 (struct dentry_t*) ; 
 scalar_t__ stub7 (struct dentry_t*) ; 
 scalar_t__ stub8 (struct dentry_t*) ; 
 int /*<<< orphan*/  stub9 (struct dentry_t*,scalar_t__) ; 

s32 move_file(struct inode *inode, struct chain_t *p_olddir, s32 oldentry,
	      struct chain_t *p_newdir, struct uni_name_t *p_uniname,
	      struct file_id_t *fid)
{
	s32 ret, newentry, num_new_entries, num_old_entries;
	sector_t sector_mov, sector_new;
	struct chain_t clu;
	struct dos_name_t dos_name;
	struct dentry_t *epmov, *epnew;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct fs_func *fs_func = p_fs->fs_func;

	epmov = get_entry_in_dir(sb, p_olddir, oldentry, &sector_mov);
	if (!epmov)
		return FFS_MEDIAERR;

	/* check if the source and target directory is the same */
	if (fs_func->get_entry_type(epmov) == TYPE_DIR &&
	    fs_func->get_entry_clu0(epmov) == p_newdir->dir)
		return FFS_INVALIDPATH;

	buf_lock(sb, sector_mov);

	/* buf_lock() before call count_ext_entries() */
	num_old_entries = fs_func->count_ext_entries(sb, p_olddir, oldentry,
						     epmov);
	if (num_old_entries < 0) {
		buf_unlock(sb, sector_mov);
		return FFS_MEDIAERR;
	}
	num_old_entries++;

	ret = get_num_entries_and_dos_name(sb, p_newdir, p_uniname,
					   &num_new_entries, &dos_name);
	if (ret) {
		buf_unlock(sb, sector_mov);
		return ret;
	}

	newentry = find_empty_entry(inode, p_newdir, num_new_entries);
	if (newentry < 0) {
		buf_unlock(sb, sector_mov);
		return FFS_FULL;
	}

	epnew = get_entry_in_dir(sb, p_newdir, newentry, &sector_new);
	if (!epnew) {
		buf_unlock(sb, sector_mov);
		return FFS_MEDIAERR;
	}

	memcpy((void *)epnew, (void *)epmov, DENTRY_SIZE);
	if (fs_func->get_entry_type(epnew) == TYPE_FILE) {
		fs_func->set_entry_attr(epnew, fs_func->get_entry_attr(epnew) |
					ATTR_ARCHIVE);
		fid->attr |= ATTR_ARCHIVE;
	}
	buf_modify(sb, sector_new);
	buf_unlock(sb, sector_mov);

	if (p_fs->vol_type == EXFAT) {
		epmov = get_entry_in_dir(sb, p_olddir, oldentry + 1,
					 &sector_mov);
		buf_lock(sb, sector_mov);
		epnew = get_entry_in_dir(sb, p_newdir, newentry + 1,
					 &sector_new);
		if (!epmov || !epnew) {
			buf_unlock(sb, sector_mov);
			return FFS_MEDIAERR;
		}

		memcpy((void *)epnew, (void *)epmov, DENTRY_SIZE);
		buf_modify(sb, sector_new);
		buf_unlock(sb, sector_mov);
	} else if (fs_func->get_entry_type(epnew) == TYPE_DIR) {
		/* change ".." pointer to new parent dir */
		clu.dir = fs_func->get_entry_clu0(epnew);
		clu.flags = 0x01;

		epnew = get_entry_in_dir(sb, &clu, 1, &sector_new);
		if (!epnew)
			return FFS_MEDIAERR;

		if (p_newdir->dir == p_fs->root_dir)
			fs_func->set_entry_clu0(epnew, CLUSTER_32(0));
		else
			fs_func->set_entry_clu0(epnew, p_newdir->dir);
		buf_modify(sb, sector_new);
	}

	ret = fs_func->init_ext_entry(sb, p_newdir, newentry, num_new_entries,
				      p_uniname, &dos_name);
	if (ret != FFS_SUCCESS)
		return ret;

	fs_func->delete_dir_entry(sb, p_olddir, oldentry, 0, num_old_entries);

	fid->dir.dir = p_newdir->dir;
	fid->dir.size = p_newdir->size;
	fid->dir.flags = p_newdir->flags;

	fid->entry = newentry;

	return FFS_SUCCESS;
}