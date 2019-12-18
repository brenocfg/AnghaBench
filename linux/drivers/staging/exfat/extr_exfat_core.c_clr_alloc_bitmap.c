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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {int map_clu; int sectors_per_clu_bits; TYPE_1__** vol_amap; } ;
struct bd_info_t {int sector_size_bits; int sector_size; } ;
struct exfat_mount_options {scalar_t__ discard; } ;
struct exfat_sb_info {struct bd_info_t bd_info; struct fs_info_t fs_info; struct exfat_mount_options options; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ START_SECTOR (int) ; 
 int /*<<< orphan*/  exfat_bitmap_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int sb_issue_discard (struct super_block*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_write (struct super_block*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 

s32 clr_alloc_bitmap(struct super_block *sb, u32 clu)
{
	int i, b;
	sector_t sector;
#ifdef CONFIG_EXFAT_DISCARD
	struct exfat_sb_info *sbi = EXFAT_SB(sb);
	struct exfat_mount_options *opts = &sbi->options;
	int ret;
#endif /* CONFIG_EXFAT_DISCARD */
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	i = clu >> (p_bd->sector_size_bits + 3);
	b = clu & ((p_bd->sector_size << 3) - 1);

	sector = START_SECTOR(p_fs->map_clu) + i;

	exfat_bitmap_clear((u8 *)p_fs->vol_amap[i]->b_data, b);

	return sector_write(sb, sector, p_fs->vol_amap[i], 0);

#ifdef CONFIG_EXFAT_DISCARD
	if (opts->discard) {
		ret = sb_issue_discard(sb, START_SECTOR(clu),
				       (1 << p_fs->sectors_per_clu_bits),
				       GFP_NOFS, 0);
		if (ret == -EOPNOTSUPP) {
			pr_warn("discard not supported by device, disabling");
			opts->discard = 0;
		}
	}
#endif /* CONFIG_EXFAT_DISCARD */
}