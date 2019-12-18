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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__** vol_utbl; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bd_info_t {int sector_size; } ;
typedef  scalar_t__ sector_t ;
typedef  int s32 ;
struct TYPE_2__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FFS_ERROR ; 
 int FFS_MEMORYERR ; 
 int FFS_SUCCESS ; 
 scalar_t__ GET16 (int*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LOW_INDEX_BIT ; 
 int UTBL_COL_COUNT ; 
 scalar_t__ UTBL_ROW_COUNT ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  free_upcase_table (struct super_block*) ; 
 scalar_t__ get_col_index (scalar_t__) ; 
 size_t get_row_index (scalar_t__) ; 
 scalar_t__** kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__* kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 
 int sector_read (struct super_block*,scalar_t__,struct buffer_head**,int) ; 

__attribute__((used)) static s32 __load_upcase_table(struct super_block *sb, sector_t sector,
			       u32 num_sectors, u32 utbl_checksum)
{
	int i, ret = FFS_ERROR;
	u32 j;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);
	struct buffer_head *tmp_bh = NULL;
	sector_t end_sector = num_sectors + sector;

	bool	skip = false;
	u32	index = 0;
	u16	uni = 0;
	u16 **upcase_table;

	u32 checksum = 0;

	upcase_table = p_fs->vol_utbl = kmalloc(UTBL_COL_COUNT * sizeof(u16 *),
						GFP_KERNEL);
	if (!upcase_table)
		return FFS_MEMORYERR;
	memset(upcase_table, 0, UTBL_COL_COUNT * sizeof(u16 *));

	while (sector < end_sector) {
		ret = sector_read(sb, sector, &tmp_bh, 1);
		if (ret != FFS_SUCCESS) {
			pr_debug("sector read (0x%llX)fail\n",
				 (unsigned long long)sector);
			goto error;
		}
		sector++;

		for (i = 0; i < p_bd->sector_size && index <= 0xFFFF; i += 2) {
			uni = GET16(((u8 *)tmp_bh->b_data) + i);

			checksum = ((checksum & 1) ? 0x80000000 : 0) +
				   (checksum >> 1) + *(((u8 *)tmp_bh->b_data) +
						       i);
			checksum = ((checksum & 1) ? 0x80000000 : 0) +
				   (checksum >> 1) + *(((u8 *)tmp_bh->b_data) +
						       (i + 1));

			if (skip) {
				pr_debug("skip from 0x%X ", index);
				index += uni;
				pr_debug("to 0x%X (amount of 0x%X)\n",
					 index, uni);
				skip = false;
			} else if (uni == index) {
				index++;
			} else if (uni == 0xFFFF) {
				skip = true;
			} else { /* uni != index , uni != 0xFFFF */
				u16 col_index = get_col_index(index);

				if (!upcase_table[col_index]) {
					pr_debug("alloc = 0x%X\n", col_index);
					upcase_table[col_index] = kmalloc_array(UTBL_ROW_COUNT,
						sizeof(u16), GFP_KERNEL);
					if (!upcase_table[col_index]) {
						ret = FFS_MEMORYERR;
						goto error;
					}

					for (j = 0; j < UTBL_ROW_COUNT; j++)
						upcase_table[col_index][j] = (col_index << LOW_INDEX_BIT) | j;
				}

				upcase_table[col_index][get_row_index(index)] = uni;
				index++;
			}
		}
	}
	if (index >= 0xFFFF && utbl_checksum == checksum) {
		if (tmp_bh)
			brelse(tmp_bh);
		return FFS_SUCCESS;
	}
	ret = FFS_ERROR;
error:
	if (tmp_bh)
		brelse(tmp_bh);
	free_upcase_table(sb);
	return ret;
}