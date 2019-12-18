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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct super_block {int dummy; } ;
struct fs_info_t {scalar_t__ vol_type; scalar_t__ FAT1_start_sector; } ;
struct bd_info_t {int sector_size_bits; int sector_size_mask; int sector_size; } ;
typedef  scalar_t__ sector_t ;
typedef  int s32 ;
struct TYPE_2__ {struct bd_info_t bd_info; struct fs_info_t fs_info; } ;

/* Variables and functions */
 int CLUSTER_16 (int) ; 
 int CLUSTER_32 (int) ; 
 scalar_t__ EXFAT ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 scalar_t__ FAT32 ; 
 scalar_t__* FAT_getblk (struct super_block*,scalar_t__) ; 
 int GET16 (scalar_t__*) ; 
 int GET16_A (scalar_t__*) ; 
 int GET32_A (scalar_t__*) ; 

__attribute__((used)) static int __FAT_read(struct super_block *sb, u32 loc, u32 *content)
{
	s32 off;
	u32 _content;
	sector_t sec;
	u8 *fat_sector, *fat_entry;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);

	if (p_fs->vol_type == FAT12) {
		sec = p_fs->FAT1_start_sector +
			((loc + (loc >> 1)) >> p_bd->sector_size_bits);
		off = (loc + (loc >> 1)) & p_bd->sector_size_mask;

		if (off == (p_bd->sector_size - 1)) {
			fat_sector = FAT_getblk(sb, sec);
			if (!fat_sector)
				return -1;

			_content = (u32)fat_sector[off];

			fat_sector = FAT_getblk(sb, ++sec);
			if (!fat_sector)
				return -1;

			_content |= (u32)fat_sector[0] << 8;
		} else {
			fat_sector = FAT_getblk(sb, sec);
			if (!fat_sector)
				return -1;

			fat_entry = &fat_sector[off];
			_content = GET16(fat_entry);
		}

		if (loc & 1)
			_content >>= 4;

		_content &= 0x00000FFF;

		if (_content >= CLUSTER_16(0x0FF8)) {
			*content = CLUSTER_32(~0);
			return 0;
		}
		*content = CLUSTER_32(_content);
		return 0;
	} else if (p_fs->vol_type == FAT16) {
		sec = p_fs->FAT1_start_sector +
			(loc >> (p_bd->sector_size_bits - 1));
		off = (loc << 1) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		fat_entry = &fat_sector[off];

		_content = GET16_A(fat_entry);

		_content &= 0x0000FFFF;

		if (_content >= CLUSTER_16(0xFFF8)) {
			*content = CLUSTER_32(~0);
			return 0;
		}
		*content = CLUSTER_32(_content);
		return 0;
	} else if (p_fs->vol_type == FAT32) {
		sec = p_fs->FAT1_start_sector +
			(loc >> (p_bd->sector_size_bits - 2));
		off = (loc << 2) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		fat_entry = &fat_sector[off];

		_content = GET32_A(fat_entry);

		_content &= 0x0FFFFFFF;

		if (_content >= CLUSTER_32(0x0FFFFFF8)) {
			*content = CLUSTER_32(~0);
			return 0;
		}
		*content = CLUSTER_32(_content);
		return 0;
	} else if (p_fs->vol_type == EXFAT) {
		sec = p_fs->FAT1_start_sector +
			(loc >> (p_bd->sector_size_bits - 2));
		off = (loc << 2) & p_bd->sector_size_mask;

		fat_sector = FAT_getblk(sb, sec);
		if (!fat_sector)
			return -1;

		fat_entry = &fat_sector[off];
		_content = GET32_A(fat_entry);

		if (_content >= CLUSTER_32(0xFFFFFFF8)) {
			*content = CLUSTER_32(~0);
			return 0;
		}
		*content = CLUSTER_32(_content);
		return 0;
	}

	/* Unknown volume type, throw in the towel and go home */
	*content = CLUSTER_32(~0);
	return 0;
}