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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ vol_type; scalar_t__ FAT1_start_sector; } ;
struct bd_info_t {int sector_size_bits; int sector_size_mask; int sector_size; } ;
typedef  scalar_t__ sector_t ;
typedef  int s32 ;
struct TYPE_2__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 scalar_t__ FAT32 ; 
 int* FAT_getblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  FAT_modify (struct super_block*,scalar_t__) ; 
 int GET16 (int*) ; 
 int GET32_A (int*) ; 
 int /*<<< orphan*/  SET16 (int*,int) ; 
 int /*<<< orphan*/  SET16_A (int*,int) ; 
 int /*<<< orphan*/  SET32_A (int*,int) ; 

__attribute__((used)) static s32 __FAT_write(struct super_block *sb, u32 loc, u32 content)
{
	s32 off;
	sector_t sec;
	u8 *fat_sector, *fat_entry;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	if (p_fs->vol_type == FAT12) {
		content &= 0x00000FFF;

		sec = p_fs->FAT1_start_sector +
			((loc + (loc >> 1)) >> p_bd->sector_size_bits);
		off = (loc + (loc >> 1)) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		if (loc & 1) { /* odd */
			content <<= 4;

			if (off == (p_bd->sector_size - 1)) {
				fat_sector[off] = (u8)(content |
						       (fat_sector[off] &
							0x0F));
				FAT_modify(sb, sec);

				fat_sector = FAT_getblk(sb, ++sec);
				if (!fat_sector)
					return -1;

				fat_sector[0] = (u8)(content >> 8);
			} else {
				fat_entry = &fat_sector[off];
				content |= GET16(fat_entry) & 0x000F;

				SET16(fat_entry, content);
			}
		} else { /* even */
			fat_sector[off] = (u8)(content);

			if (off == (p_bd->sector_size - 1)) {
				fat_sector[off] = (u8)(content);
				FAT_modify(sb, sec);

				fat_sector = FAT_getblk(sb, ++sec);
				if (!fat_sector)
					return -1;
				fat_sector[0] = (u8)((fat_sector[0] & 0xF0) |
						     (content >> 8));
			} else {
				fat_entry = &fat_sector[off];
				content |= GET16(fat_entry) & 0xF000;

				SET16(fat_entry, content);
			}
		}
	}

	else if (p_fs->vol_type == FAT16) {
		content &= 0x0000FFFF;

		sec = p_fs->FAT1_start_sector + (loc >>
						 (p_bd->sector_size_bits - 1));
		off = (loc << 1) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		fat_entry = &fat_sector[off];

		SET16_A(fat_entry, content);
	} else if (p_fs->vol_type == FAT32) {
		content &= 0x0FFFFFFF;

		sec = p_fs->FAT1_start_sector + (loc >>
						 (p_bd->sector_size_bits - 2));
		off = (loc << 2) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		fat_entry = &fat_sector[off];

		content |= GET32_A(fat_entry) & 0xF0000000;

		SET32_A(fat_entry, content);
	} else { /* p_fs->vol_type == EXFAT */
		sec = p_fs->FAT1_start_sector + (loc >>
						 (p_bd->sector_size_bits - 2));
		off = (loc << 2) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		fat_entry = &fat_sector[off];

		SET32_A(fat_entry, content);
	}

	FAT_modify(sb, sec);
	return 0;
}