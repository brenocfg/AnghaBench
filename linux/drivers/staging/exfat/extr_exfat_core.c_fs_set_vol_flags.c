#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct super_block {int dummy; } ;
struct pbr_sector_t {scalar_t__ bpb; } ;
struct fs_info_t {scalar_t__ vol_flag; scalar_t__ vol_type; TYPE_1__* pbr_bh; int /*<<< orphan*/  PBR_sector; } ;
struct bpbex_t {int /*<<< orphan*/  vol_flags; } ;
struct TYPE_6__ {struct fs_info_t fs_info; } ;
struct TYPE_5__ {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ EXFAT ; 
 TYPE_4__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FFS_SUCCESS ; 
 int /*<<< orphan*/  SET16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VOL_DIRTY ; 
 int /*<<< orphan*/  buffer_dirty (TYPE_1__*) ; 
 scalar_t__ sector_read (struct super_block*,int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int /*<<< orphan*/  sector_write (struct super_block*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void fs_set_vol_flags(struct super_block *sb, u32 new_flag)
{
	struct pbr_sector_t *p_pbr;
	struct bpbex_t *p_bpb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if (p_fs->vol_flag == new_flag)
		return;

	p_fs->vol_flag = new_flag;

	if (p_fs->vol_type == EXFAT) {
		if (!p_fs->pbr_bh) {
			if (sector_read(sb, p_fs->PBR_sector,
					&p_fs->pbr_bh, 1) != FFS_SUCCESS)
				return;
		}

		p_pbr = (struct pbr_sector_t *)p_fs->pbr_bh->b_data;
		p_bpb = (struct bpbex_t *)p_pbr->bpb;
		SET16(p_bpb->vol_flags, (u16)new_flag);

		/* XXX duyoung
		 * what can we do here? (cuz fs_set_vol_flags() is void)
		 */
		if ((new_flag == VOL_DIRTY) && (!buffer_dirty(p_fs->pbr_bh)))
			sector_write(sb, p_fs->PBR_sector, p_fs->pbr_bh, 1);
		else
			sector_write(sb, p_fs->PBR_sector, p_fs->pbr_bh, 0);
	}
}