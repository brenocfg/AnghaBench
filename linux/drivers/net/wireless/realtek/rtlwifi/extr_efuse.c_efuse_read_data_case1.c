#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int PG_STATE_DATA ; 
 int PG_STATE_HEADER ; 
 int efuse_calculate_word_cnts (int) ; 
 scalar_t__ efuse_one_byte_read (struct ieee80211_hw*,scalar_t__,int*) ; 

__attribute__((used)) static void efuse_read_data_case1(struct ieee80211_hw *hw, u16 *efuse_addr,
				u8 efuse_data, u8 offset, u8 *tmpdata,
				u8 *readstate)
{
	bool dataempty = true;
	u8 hoffset;
	u8 tmpidx;
	u8 hworden;
	u8 word_cnts;

	hoffset = (efuse_data >> 4) & 0x0F;
	hworden = efuse_data & 0x0F;
	word_cnts = efuse_calculate_word_cnts(hworden);

	if (hoffset == offset) {
		for (tmpidx = 0; tmpidx < word_cnts * 2; tmpidx++) {
			if (efuse_one_byte_read(hw, *efuse_addr + 1 + tmpidx,
						&efuse_data)) {
				tmpdata[tmpidx] = efuse_data;
				if (efuse_data != 0xff)
					dataempty = false;
			}
		}

		if (!dataempty) {
			*readstate = PG_STATE_DATA;
		} else {
			*efuse_addr = *efuse_addr + (word_cnts * 2) + 1;
			*readstate = PG_STATE_HEADER;
		}

	} else {
		*efuse_addr = *efuse_addr + (word_cnts * 2) + 1;
		*readstate = PG_STATE_HEADER;
	}
}