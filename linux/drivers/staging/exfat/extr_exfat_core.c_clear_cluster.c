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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ root_start_sector; scalar_t__ data_start_sector; scalar_t__ sectors_per_clu; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bd_info_t {int /*<<< orphan*/  sector_size; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FFS_SUCCESS ; 
 scalar_t__ START_SECTOR (scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sector_read (struct super_block*,scalar_t__,struct buffer_head**,int /*<<< orphan*/ ) ; 
 scalar_t__ sector_write (struct super_block*,scalar_t__,struct buffer_head*,int /*<<< orphan*/ ) ; 

s32 clear_cluster(struct super_block *sb, u32 clu)
{
	sector_t s, n;
	s32 ret = FFS_SUCCESS;
	struct buffer_head *tmp_bh = NULL;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	if (clu == CLUSTER_32(0)) { /* FAT16 root_dir */
		s = p_fs->root_start_sector;
		n = p_fs->data_start_sector;
	} else {
		s = START_SECTOR(clu);
		n = s + p_fs->sectors_per_clu;
	}

	for (; s < n; s++) {
		ret = sector_read(sb, s, &tmp_bh, 0);
		if (ret != FFS_SUCCESS)
			return ret;

		memset((char *)tmp_bh->b_data, 0x0, p_bd->sector_size);
		ret = sector_write(sb, s, tmp_bh, 0);
		if (ret != FFS_SUCCESS)
			break;
	}

	brelse(tmp_bh);
	return ret;
}