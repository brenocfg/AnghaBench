#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {int i_blocks; struct super_block* i_sb; } ;
struct TYPE_6__ {int flags; scalar_t__ dir; scalar_t__ size; } ;
struct TYPE_7__ {int entry; scalar_t__ dir; TYPE_1__ clu; } ;
struct fs_info_t {scalar_t__ vol_type; scalar_t__ root_dir; int cluster_size_bits; scalar_t__ cluster_size; TYPE_3__* fs_func; TYPE_2__ hint_uentry; scalar_t__ dev_ejected; } ;
struct file_id_t {int flags; int /*<<< orphan*/  size; scalar_t__ entry; int /*<<< orphan*/  dir; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; int size; int flags; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int s32 ;
struct TYPE_10__ {struct file_id_t fid; int /*<<< orphan*/  mmu_private; } ;
struct TYPE_9__ {struct fs_info_t fs_info; } ;
struct TYPE_8__ {int (* alloc_cluster ) (struct super_block*,int,struct chain_t*) ;int /*<<< orphan*/  (* set_entry_flag ) (struct dentry_t*,int) ;int /*<<< orphan*/  (* set_entry_size ) (struct dentry_t*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 int DENTRY_SIZE_BITS ; 
 scalar_t__ EXFAT ; 
 TYPE_5__* EXFAT_I (struct inode*) ; 
 TYPE_4__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_write (struct super_block*,scalar_t__,scalar_t__) ; 
 scalar_t__ FFS_SUCCESS ; 
 int /*<<< orphan*/  buf_modify (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ clear_cluster (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  exfat_chain_cont_cluster (struct super_block*,scalar_t__,int) ; 
 scalar_t__ find_last_cluster (struct super_block*,struct chain_t*) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int search_deleted_or_unused_entry (struct super_block*,struct chain_t*,int) ; 
 int stub1 (struct super_block*,int,struct chain_t*) ; 
 int /*<<< orphan*/  stub2 (struct dentry_t*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct dentry_t*,int) ; 
 int /*<<< orphan*/  update_dir_checksum (struct super_block*,int /*<<< orphan*/ *,scalar_t__) ; 

s32 find_empty_entry(struct inode *inode, struct chain_t *p_dir, s32 num_entries)
{
	s32 ret, dentry;
	u32 last_clu;
	sector_t sector;
	u64 size = 0;
	struct chain_t clu;
	struct dentry_t *ep = NULL;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct file_id_t *fid = &(EXFAT_I(inode)->fid);

	if (p_dir->dir == CLUSTER_32(0)) /* FAT16 root_dir */
		return search_deleted_or_unused_entry(sb, p_dir, num_entries);

	while ((dentry = search_deleted_or_unused_entry(sb, p_dir, num_entries)) < 0) {
		if (p_fs->dev_ejected)
			break;

		if (p_fs->vol_type == EXFAT) {
			if (p_dir->dir != p_fs->root_dir)
				size = i_size_read(inode);
		}

		last_clu = find_last_cluster(sb, p_dir);
		clu.dir = last_clu + 1;
		clu.size = 0;
		clu.flags = p_dir->flags;

		/* (1) allocate a cluster */
		ret = p_fs->fs_func->alloc_cluster(sb, 1, &clu);
		if (ret < 1)
			return -1;

		if (clear_cluster(sb, clu.dir) != FFS_SUCCESS)
			return -1;

		/* (2) append to the FAT chain */
		if (clu.flags != p_dir->flags) {
			exfat_chain_cont_cluster(sb, p_dir->dir, p_dir->size);
			p_dir->flags = 0x01;
			p_fs->hint_uentry.clu.flags = 0x01;
		}
		if (clu.flags == 0x01)
			if (FAT_write(sb, last_clu, clu.dir) < 0)
				return -1;

		if (p_fs->hint_uentry.entry == -1) {
			p_fs->hint_uentry.dir = p_dir->dir;
			p_fs->hint_uentry.entry = p_dir->size << (p_fs->cluster_size_bits - DENTRY_SIZE_BITS);

			p_fs->hint_uentry.clu.dir = clu.dir;
			p_fs->hint_uentry.clu.size = 0;
			p_fs->hint_uentry.clu.flags = clu.flags;
		}
		p_fs->hint_uentry.clu.size++;
		p_dir->size++;

		/* (3) update the directory entry */
		if (p_fs->vol_type == EXFAT) {
			if (p_dir->dir != p_fs->root_dir) {
				size += p_fs->cluster_size;

				ep = get_entry_in_dir(sb, &fid->dir,
						      fid->entry + 1, &sector);
				if (!ep)
					return -1;
				p_fs->fs_func->set_entry_size(ep, size);
				p_fs->fs_func->set_entry_flag(ep, p_dir->flags);
				buf_modify(sb, sector);

				update_dir_checksum(sb, &(fid->dir),
						    fid->entry);
			}
		}

		i_size_write(inode, i_size_read(inode) + p_fs->cluster_size);
		EXFAT_I(inode)->mmu_private += p_fs->cluster_size;
		EXFAT_I(inode)->fid.size += p_fs->cluster_size;
		EXFAT_I(inode)->fid.flags = p_dir->flags;
		inode->i_blocks += 1 << (p_fs->cluster_size_bits - 9);
	}

	return dentry;
}