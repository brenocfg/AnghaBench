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
struct inode {int i_generation; int i_blocks; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; TYPE_2__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; void* i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_sb; } ;
struct fs_info_t {int cluster_size; } ;
struct file_id_t {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs_gid; int /*<<< orphan*/  fs_uid; } ;
struct exfat_sb_info {TYPE_1__ options; struct fs_info_t fs_info; } ;
struct dir_entry_t {int Attr; int /*<<< orphan*/  AccessTimestamp; int /*<<< orphan*/  CreateTimestamp; int /*<<< orphan*/  ModifyTimestamp; int /*<<< orphan*/  Size; int /*<<< orphan*/  NumSubdirs; } ;
typedef  int loff_t ;
struct TYPE_6__ {int mmu_private; int /*<<< orphan*/ * target; scalar_t__ i_pos; int /*<<< orphan*/  fid; } ;
struct TYPE_5__ {scalar_t__ nrpages; int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ATTR_SUBDIR ; 
 int ATTR_SYMLINK ; 
 TYPE_3__* EXFAT_I (struct inode*) ; 
 struct exfat_sb_info* EXFAT_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INC_IVERSION (struct inode*) ; 
 int /*<<< orphan*/  exfat_aops ; 
 int /*<<< orphan*/  exfat_dir_inode_operations ; 
 int /*<<< orphan*/  exfat_dir_operations ; 
 int /*<<< orphan*/  exfat_file_inode_operations ; 
 int /*<<< orphan*/  exfat_file_operations ; 
 void* exfat_make_mode (struct exfat_sb_info*,int,int) ; 
 int /*<<< orphan*/  exfat_save_attr (struct inode*,int) ; 
 int /*<<< orphan*/  exfat_symlink_inode_operations ; 
 int /*<<< orphan*/  exfat_time_fat2unix (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffsReadStat (struct inode*,struct dir_entry_t*) ; 
 int get_seconds () ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct file_id_t*,int) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exfat_fill_inode(struct inode *inode, struct file_id_t *fid)
{
	struct exfat_sb_info *sbi = EXFAT_SB(inode->i_sb);
	struct fs_info_t *p_fs = &(sbi->fs_info);
	struct dir_entry_t info;

	memcpy(&(EXFAT_I(inode)->fid), fid, sizeof(struct file_id_t));

	ffsReadStat(inode, &info);

	EXFAT_I(inode)->i_pos = 0;
	EXFAT_I(inode)->target = NULL;
	inode->i_uid = sbi->options.fs_uid;
	inode->i_gid = sbi->options.fs_gid;
	INC_IVERSION(inode);
	inode->i_generation = get_seconds();

	if (info.Attr & ATTR_SUBDIR) { /* directory */
		inode->i_generation &= ~1;
		inode->i_mode = exfat_make_mode(sbi, info.Attr, 0777);
		inode->i_op = &exfat_dir_inode_operations;
		inode->i_fop = &exfat_dir_operations;

		i_size_write(inode, info.Size);
		EXFAT_I(inode)->mmu_private = i_size_read(inode);
		set_nlink(inode, info.NumSubdirs);
	} else if (info.Attr & ATTR_SYMLINK) { /* symbolic link */
		inode->i_generation |= 1;
		inode->i_mode = exfat_make_mode(sbi, info.Attr, 0777);
		inode->i_op = &exfat_symlink_inode_operations;

		i_size_write(inode, info.Size);
		EXFAT_I(inode)->mmu_private = i_size_read(inode);
	} else { /* regular file */
		inode->i_generation |= 1;
		inode->i_mode = exfat_make_mode(sbi, info.Attr, 0777);
		inode->i_op = &exfat_file_inode_operations;
		inode->i_fop = &exfat_file_operations;
		inode->i_mapping->a_ops = &exfat_aops;
		inode->i_mapping->nrpages = 0;

		i_size_write(inode, info.Size);
		EXFAT_I(inode)->mmu_private = i_size_read(inode);
	}
	exfat_save_attr(inode, info.Attr);

	inode->i_blocks = ((i_size_read(inode) + (p_fs->cluster_size - 1))
				& ~((loff_t)p_fs->cluster_size - 1)) >> 9;

	exfat_time_fat2unix(&inode->i_mtime, &info.ModifyTimestamp);
	exfat_time_fat2unix(&inode->i_ctime, &info.CreateTimestamp);
	exfat_time_fat2unix(&inode->i_atime, &info.AccessTimestamp);

	return 0;
}