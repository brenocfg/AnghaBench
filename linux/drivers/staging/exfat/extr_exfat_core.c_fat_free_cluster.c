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
struct fs_info_t {int sectors_per_clu; scalar_t__ used_clusters; scalar_t__ dev_ejected; } ;
struct chain_t {scalar_t__ dir; scalar_t__ size; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 scalar_t__ FAT_write (struct super_block*,scalar_t__,scalar_t__) ; 
 scalar_t__ START_SECTOR (scalar_t__) ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  __set_sb_dirty (struct super_block*) ; 
 int /*<<< orphan*/  buf_release (struct super_block*,scalar_t__) ; 

void fat_free_cluster(struct super_block *sb, struct chain_t *p_chain,
		      s32 do_relse)
{
	s32 num_clusters = 0;
	u32 clu, prev;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	int i;
	sector_t sector;

	if ((p_chain->dir == CLUSTER_32(0)) || (p_chain->dir == CLUSTER_32(~0)))
		return;
	__set_sb_dirty(sb);
	clu = p_chain->dir;

	if (p_chain->size <= 0)
		return;

	do {
		if (p_fs->dev_ejected)
			break;

		if (do_relse) {
			sector = START_SECTOR(clu);
			for (i = 0; i < p_fs->sectors_per_clu; i++)
				buf_release(sb, sector + i);
		}

		prev = clu;
		if (FAT_read(sb, clu, &clu) == -1)
			break;

		if (FAT_write(sb, prev, CLUSTER_32(0)) < 0)
			break;
		num_clusters++;

	} while (clu != CLUSTER_32(~0));

	if (p_fs->used_clusters != UINT_MAX)
		p_fs->used_clusters -= num_clusters;
}