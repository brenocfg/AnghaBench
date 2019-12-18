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
typedef  size_t u8 ;
struct super_block {int dummy; } ;
struct fs_info_t {int num_clusters; TYPE_1__** vol_amap; } ;
struct bd_info_t {int sector_size; } ;
typedef  int s32 ;
struct TYPE_4__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;
struct TYPE_3__ {scalar_t__ b_data; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 scalar_t__* used_bit ; 

s32 exfat_count_used_clusters(struct super_block *sb)
{
	int i, map_i, map_b, count = 0;
	u8 k;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	map_i = map_b = 0;

	for (i = 2; i < p_fs->num_clusters; i += 8) {
		k = *(((u8 *)p_fs->vol_amap[map_i]->b_data) + map_b);
		count += used_bit[k];

		if ((++map_b) >= p_bd->sector_size) {
			map_i++;
			map_b = 0;
		}
	}

	return count;
}