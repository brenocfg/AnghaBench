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
struct super_block {unsigned long s_blocksize; unsigned char s_blocksize_bits; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct fs_info_t {scalar_t__ vol_type; int dentries_in_root; int root_start_sector; int sectors_per_clu_bits; int sectors_per_clu; } ;
struct bd_info_t {int sector_size_bits; } ;
struct exfat_sb_info {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;
typedef  int sector_t ;
struct TYPE_3__ {unsigned long size; } ;
struct TYPE_4__ {TYPE_1__ fid; } ;

/* Variables and functions */
 unsigned int CLUSTER_32 (int /*<<< orphan*/ ) ; 
 int DENTRY_SIZE_BITS ; 
 int EIO ; 
 int ENOSPC ; 
 TYPE_2__* EXFAT_I (struct inode*) ; 
 scalar_t__ EXFAT_ROOT_INO ; 
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 int FFS_FULL ; 
 int START_SECTOR (unsigned int) ; 
 int ffsMapCluster (struct inode*,int,unsigned int*) ; 
 unsigned long const i_size_read (struct inode*) ; 

__attribute__((used)) static int exfat_bmap(struct inode *inode, sector_t sector, sector_t *phys,
		      unsigned long *mapped_blocks, int *create)
{
	struct super_block *sb = inode->i_sb;
	struct exfat_sb_info *sbi = EXFAT_SB(sb);
	struct fs_info_t *p_fs = &(sbi->fs_info);
	struct bd_info_t *p_bd = &(sbi->bd_info);
	const unsigned long blocksize = sb->s_blocksize;
	const unsigned char blocksize_bits = sb->s_blocksize_bits;
	sector_t last_block;
	int err, clu_offset, sec_offset;
	unsigned int cluster;

	*phys = 0;
	*mapped_blocks = 0;

	if ((p_fs->vol_type == FAT12) || (p_fs->vol_type == FAT16)) {
		if (inode->i_ino == EXFAT_ROOT_INO) {
			if (sector <
			    (p_fs->dentries_in_root >>
			     (p_bd->sector_size_bits - DENTRY_SIZE_BITS))) {
				*phys = sector + p_fs->root_start_sector;
				*mapped_blocks = 1;
			}
			return 0;
		}
	}

	last_block = (i_size_read(inode) + (blocksize - 1)) >> blocksize_bits;
	if (sector >= last_block) {
		if (*create == 0)
			return 0;
	} else {
		*create = 0;
	}

	/* cluster offset */
	clu_offset = sector >> p_fs->sectors_per_clu_bits;

	/* sector offset in cluster */
	sec_offset = sector & (p_fs->sectors_per_clu - 1);

	EXFAT_I(inode)->fid.size = i_size_read(inode);

	err = ffsMapCluster(inode, clu_offset, &cluster);

	if (err) {
		if (err == FFS_FULL)
			return -ENOSPC;
		else
			return -EIO;
	} else if (cluster != CLUSTER_32(~0)) {
		*phys = START_SECTOR(cluster) + sec_offset;
		*mapped_blocks = p_fs->sectors_per_clu - sec_offset;
	}

	return 0;
}