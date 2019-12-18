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
typedef  int u8 ;
typedef  int u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {int num_clusters; int map_sectors; TYPE_1__** vol_amap; } ;
struct bd_info_t {int sector_size_bits; int sector_size_mask; int sector_size; } ;
struct TYPE_4__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int CLUSTER_32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 int* free_bit ; 

u32 test_alloc_bitmap(struct super_block *sb, u32 clu)
{
	int i, map_i, map_b;
	u32 clu_base, clu_free;
	u8 k, clu_mask;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	clu_base = (clu & ~(0x7)) + 2;
	clu_mask = (1 << (clu - clu_base + 2)) - 1;

	map_i = clu >> (p_bd->sector_size_bits + 3);
	map_b = (clu >> 3) & p_bd->sector_size_mask;

	for (i = 2; i < p_fs->num_clusters; i += 8) {
		k = *(((u8 *)p_fs->vol_amap[map_i]->b_data) + map_b);
		if (clu_mask > 0) {
			k |= clu_mask;
			clu_mask = 0;
		}
		if (k < 0xFF) {
			clu_free = clu_base + free_bit[k];
			if (clu_free < p_fs->num_clusters)
				return clu_free;
		}
		clu_base += 8;

		if (((++map_b) >= p_bd->sector_size) ||
		    (clu_base >= p_fs->num_clusters)) {
			if ((++map_i) >= p_fs->map_sectors) {
				clu_base = 2;
				map_i = 0;
			}
			map_b = 0;
		}
	}

	return CLUSTER_32(~0);
}