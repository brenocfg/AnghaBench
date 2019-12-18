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
struct uni_name_t {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {scalar_t__ vol_type; struct fs_func* fs_func; } ;
struct fs_func {scalar_t__ (* count_ext_entries ) (struct super_block*,struct chain_t*,scalar_t__,struct dentry_t*) ;scalar_t__ (* get_entry_type ) (struct dentry_t*) ;int (* get_entry_attr ) (struct dentry_t*) ;scalar_t__ (* init_ext_entry ) (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,struct uni_name_t*,struct dos_name_t*) ;int /*<<< orphan*/  (* delete_dir_entry ) (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* set_entry_attr ) (struct dentry_t*,int) ;} ;
struct file_id_t {int attr; scalar_t__ entry; } ;
struct dos_name_t {int dummy; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 int ATTR_ARCHIVE ; 
 int /*<<< orphan*/  DENTRY_SIZE ; 
 scalar_t__ EXFAT ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FFS_FULL ; 
 scalar_t__ FFS_MEDIAERR ; 
 scalar_t__ FFS_SUCCESS ; 
 scalar_t__ TYPE_FILE ; 
 int /*<<< orphan*/  buf_lock (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_modify (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_unlock (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_empty_entry (struct inode*,struct chain_t*,scalar_t__) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ get_num_entries_and_dos_name (struct super_block*,struct chain_t*,struct uni_name_t*,scalar_t__*,struct dos_name_t*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct super_block*,struct chain_t*,scalar_t__,struct dentry_t*) ; 
 scalar_t__ stub10 (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,struct uni_name_t*,struct dos_name_t*) ; 
 int /*<<< orphan*/  stub11 (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (struct dentry_t*) ; 
 int /*<<< orphan*/  stub3 (struct dentry_t*,int) ; 
 int stub4 (struct dentry_t*) ; 
 scalar_t__ stub5 (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,struct uni_name_t*,struct dos_name_t*) ; 
 int /*<<< orphan*/  stub6 (struct super_block*,struct chain_t*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ stub7 (struct dentry_t*) ; 
 int /*<<< orphan*/  stub8 (struct dentry_t*,int) ; 
 int stub9 (struct dentry_t*) ; 

s32 rename_file(struct inode *inode, struct chain_t *p_dir, s32 oldentry,
		struct uni_name_t *p_uniname, struct file_id_t *fid)
{
	s32 ret, newentry = -1, num_old_entries, num_new_entries;
	sector_t sector_old, sector_new;
	struct dos_name_t dos_name;
	struct dentry_t *epold, *epnew;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct fs_func *fs_func = p_fs->fs_func;

	epold = get_entry_in_dir(sb, p_dir, oldentry, &sector_old);
	if (!epold)
		return FFS_MEDIAERR;

	buf_lock(sb, sector_old);

	/* buf_lock() before call count_ext_entries() */
	num_old_entries = fs_func->count_ext_entries(sb, p_dir, oldentry,
						     epold);
	if (num_old_entries < 0) {
		buf_unlock(sb, sector_old);
		return FFS_MEDIAERR;
	}
	num_old_entries++;

	ret = get_num_entries_and_dos_name(sb, p_dir, p_uniname,
					   &num_new_entries, &dos_name);
	if (ret) {
		buf_unlock(sb, sector_old);
		return ret;
	}

	if (num_old_entries < num_new_entries) {
		newentry = find_empty_entry(inode, p_dir, num_new_entries);
		if (newentry < 0) {
			buf_unlock(sb, sector_old);
			return FFS_FULL;
		}

		epnew = get_entry_in_dir(sb, p_dir, newentry, &sector_new);
		if (!epnew) {
			buf_unlock(sb, sector_old);
			return FFS_MEDIAERR;
		}

		memcpy((void *)epnew, (void *)epold, DENTRY_SIZE);
		if (fs_func->get_entry_type(epnew) == TYPE_FILE) {
			fs_func->set_entry_attr(epnew,
						fs_func->get_entry_attr(epnew) |
						ATTR_ARCHIVE);
			fid->attr |= ATTR_ARCHIVE;
		}
		buf_modify(sb, sector_new);
		buf_unlock(sb, sector_old);

		if (p_fs->vol_type == EXFAT) {
			epold = get_entry_in_dir(sb, p_dir, oldentry + 1,
						 &sector_old);
			buf_lock(sb, sector_old);
			epnew = get_entry_in_dir(sb, p_dir, newentry + 1,
						 &sector_new);

			if (!epold || !epnew) {
				buf_unlock(sb, sector_old);
				return FFS_MEDIAERR;
			}

			memcpy((void *)epnew, (void *)epold, DENTRY_SIZE);
			buf_modify(sb, sector_new);
			buf_unlock(sb, sector_old);
		}

		ret = fs_func->init_ext_entry(sb, p_dir, newentry,
					      num_new_entries, p_uniname,
					      &dos_name);
		if (ret != FFS_SUCCESS)
			return ret;

		fs_func->delete_dir_entry(sb, p_dir, oldentry, 0,
					  num_old_entries);
		fid->entry = newentry;
	} else {
		if (fs_func->get_entry_type(epold) == TYPE_FILE) {
			fs_func->set_entry_attr(epold,
						fs_func->get_entry_attr(epold) |
						ATTR_ARCHIVE);
			fid->attr |= ATTR_ARCHIVE;
		}
		buf_modify(sb, sector_old);
		buf_unlock(sb, sector_old);

		ret = fs_func->init_ext_entry(sb, p_dir, oldentry,
					      num_new_entries, p_uniname,
					      &dos_name);
		if (ret != FFS_SUCCESS)
			return ret;

		fs_func->delete_dir_entry(sb, p_dir, oldentry, num_new_entries,
					  num_old_entries);
	}

	return FFS_SUCCESS;
}