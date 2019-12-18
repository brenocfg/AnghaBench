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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ root_dir; int dentries_per_clu; int map_sectors; int /*<<< orphan*/ * pbr_bh; int /*<<< orphan*/ ** vol_amap; int /*<<< orphan*/  map_clu; TYPE_1__* fs_func; scalar_t__ dev_ejected; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; int flags; } ;
struct buffer_head {int dummy; } ;
struct bmap_dentry_t {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  start_clu; } ;
struct bd_info_t {scalar_t__ sector_size_bits; } ;
typedef  scalar_t__ sector_t ;
typedef  int s32 ;
struct TYPE_4__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 int FFS_FORMATERR ; 
 int FFS_MEDIAERR ; 
 int FFS_MEMORYERR ; 
 int FFS_SUCCESS ; 
 int /*<<< orphan*/  GET32_A (int /*<<< orphan*/ ) ; 
 scalar_t__ GET64_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ START_SECTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_BITMAP ; 
 scalar_t__ TYPE_UNUSED ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 scalar_t__ get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int sector_read (struct super_block*,scalar_t__,int /*<<< orphan*/ **,int) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 load_alloc_bitmap(struct super_block *sb)
{
	int i, j, ret;
	u32 map_size;
	u32 type;
	sector_t sector;
	struct chain_t clu;
	struct bmap_dentry_t *ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	clu.dir = p_fs->root_dir;
	clu.flags = 0x01;

	while (clu.dir != CLUSTER_32(~0)) {
		if (p_fs->dev_ejected)
			break;

		for (i = 0; i < p_fs->dentries_per_clu; i++) {
			ep = (struct bmap_dentry_t *)get_entry_in_dir(sb, &clu,
								      i, NULL);
			if (!ep)
				return FFS_MEDIAERR;

			type = p_fs->fs_func->get_entry_type((struct dentry_t *)ep);

			if (type == TYPE_UNUSED)
				break;
			if (type != TYPE_BITMAP)
				continue;

			if (ep->flags == 0x0) {
				p_fs->map_clu  = GET32_A(ep->start_clu);
				map_size = (u32)GET64_A(ep->size);

				p_fs->map_sectors = ((map_size - 1) >> p_bd->sector_size_bits) + 1;

				p_fs->vol_amap = kmalloc_array(p_fs->map_sectors,
							       sizeof(struct buffer_head *),
							       GFP_KERNEL);
				if (!p_fs->vol_amap)
					return FFS_MEMORYERR;

				sector = START_SECTOR(p_fs->map_clu);

				for (j = 0; j < p_fs->map_sectors; j++) {
					p_fs->vol_amap[j] = NULL;
					ret = sector_read(sb, sector + j, &(p_fs->vol_amap[j]), 1);
					if (ret != FFS_SUCCESS) {
						/*  release all buffers and free vol_amap */
						i = 0;
						while (i < j)
							brelse(p_fs->vol_amap[i++]);

						kfree(p_fs->vol_amap);
						p_fs->vol_amap = NULL;
						return ret;
					}
				}

				p_fs->pbr_bh = NULL;
				return FFS_SUCCESS;
			}
		}

		if (FAT_read(sb, clu.dir, &clu.dir) != 0)
			return FFS_MEDIAERR;
	}

	return FFS_FORMATERR;
}