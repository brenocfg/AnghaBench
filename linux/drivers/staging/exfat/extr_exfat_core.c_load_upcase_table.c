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
struct fs_info_t {scalar_t__ root_dir; int dentries_per_clu; TYPE_1__* fs_func; scalar_t__ dev_ejected; } ;
struct dentry_t {int dummy; } ;
struct chain_t {scalar_t__ dir; int flags; } ;
struct case_dentry_t {int /*<<< orphan*/  checksum; int /*<<< orphan*/  size; int /*<<< orphan*/  start_clu; } ;
struct bd_info_t {scalar_t__ sector_size_bits; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ (* get_entry_type ) (struct dentry_t*) ;} ;

/* Variables and functions */
 scalar_t__ CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT_read (struct super_block*,scalar_t__,scalar_t__*) ; 
 scalar_t__ FFS_MEDIAERR ; 
 scalar_t__ FFS_SUCCESS ; 
 scalar_t__ GET32_A (int /*<<< orphan*/ ) ; 
 scalar_t__ GET64_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_SECTOR (scalar_t__) ; 
 scalar_t__ TYPE_UNUSED ; 
 scalar_t__ TYPE_UPCASE ; 
 scalar_t__ __load_default_upcase_table (struct super_block*) ; 
 scalar_t__ __load_upcase_table (struct super_block*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_entry_in_dir (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dentry_t*) ; 

s32 load_upcase_table(struct super_block *sb)
{
	int i;
	u32 tbl_clu, tbl_size;
	sector_t sector;
	u32 type, num_sectors;
	struct chain_t clu;
	struct case_dentry_t *ep;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	clu.dir = p_fs->root_dir;
	clu.flags = 0x01;

	if (p_fs->dev_ejected)
		return FFS_MEDIAERR;

	while (clu.dir != CLUSTER_32(~0)) {
		for (i = 0; i < p_fs->dentries_per_clu; i++) {
			ep = (struct case_dentry_t *)get_entry_in_dir(sb, &clu,
								      i, NULL);
			if (!ep)
				return FFS_MEDIAERR;

			type = p_fs->fs_func->get_entry_type((struct dentry_t *)ep);

			if (type == TYPE_UNUSED)
				break;
			if (type != TYPE_UPCASE)
				continue;

			tbl_clu  = GET32_A(ep->start_clu);
			tbl_size = (u32)GET64_A(ep->size);

			sector = START_SECTOR(tbl_clu);
			num_sectors = ((tbl_size - 1) >> p_bd->sector_size_bits) + 1;
			if (__load_upcase_table(sb, sector, num_sectors,
						GET32_A(ep->checksum)) != FFS_SUCCESS)
				break;
			return FFS_SUCCESS;
		}
		if (FAT_read(sb, clu.dir, &clu.dir) != 0)
			return FFS_MEDIAERR;
	}
	/* load default upcase table */
	return __load_default_upcase_table(sb);
}