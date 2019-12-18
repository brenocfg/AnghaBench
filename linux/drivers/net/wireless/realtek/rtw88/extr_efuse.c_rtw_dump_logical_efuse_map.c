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
typedef  size_t u32 ;
struct TYPE_2__ {size_t physical_size; size_t protect_size; size_t logical_size; } ;
struct rtw_dev {TYPE_1__ efuse; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t block_idx_to_logical_idx (int,int) ; 
 int get_efuse_blk_idx_1_byte (int) ; 
 int get_efuse_blk_idx_2_byte (int,int) ; 
 scalar_t__ invalid_efuse_content (int,int) ; 
 scalar_t__ invalid_efuse_header (int,int) ; 

__attribute__((used)) static int rtw_dump_logical_efuse_map(struct rtw_dev *rtwdev, u8 *phy_map,
				      u8 *log_map)
{
	u32 physical_size = rtwdev->efuse.physical_size;
	u32 protect_size = rtwdev->efuse.protect_size;
	u32 logical_size = rtwdev->efuse.logical_size;
	u32 phy_idx, log_idx;
	u8 hdr1, hdr2;
	u8 blk_idx;
	u8 word_en;
	int i;

	for (phy_idx = 0; phy_idx < physical_size - protect_size;) {
		hdr1 = phy_map[phy_idx];
		hdr2 = phy_map[phy_idx + 1];
		if (invalid_efuse_header(hdr1, hdr2))
			break;

		if ((hdr1 & 0x1f) == 0xf) {
			/* 2-byte header format */
			blk_idx = get_efuse_blk_idx_2_byte(hdr1, hdr2);
			word_en = hdr2 & 0xf;
			phy_idx += 2;
		} else {
			/* 1-byte header format */
			blk_idx = get_efuse_blk_idx_1_byte(hdr1);
			word_en = hdr1 & 0xf;
			phy_idx += 1;
		}

		for (i = 0; i < 4; i++) {
			if (invalid_efuse_content(word_en, i))
				continue;

			log_idx = block_idx_to_logical_idx(blk_idx, i);
			if (phy_idx + 1 > physical_size - protect_size ||
			    log_idx + 1 > logical_size)
				return -EINVAL;

			log_map[log_idx] = phy_map[phy_idx];
			log_map[log_idx + 1] = phy_map[phy_idx + 1];
			phy_idx += 2;
		}
	}
	return 0;
}