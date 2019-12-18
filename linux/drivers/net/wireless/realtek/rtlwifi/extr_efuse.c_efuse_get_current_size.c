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
 scalar_t__ EFUSE_MAX_SIZE ; 
 int efuse_calculate_word_cnts (int) ; 
 scalar_t__ efuse_one_byte_read (struct ieee80211_hw*,scalar_t__,int*) ; 

__attribute__((used)) static u16 efuse_get_current_size(struct ieee80211_hw *hw)
{
	int continual = true;
	u16 efuse_addr = 0;
	u8 hoffset, hworden;
	u8 efuse_data, word_cnts;

	while (continual && efuse_one_byte_read(hw, efuse_addr, &efuse_data) &&
	       (efuse_addr < EFUSE_MAX_SIZE)) {
		if (efuse_data != 0xFF) {
			hoffset = (efuse_data >> 4) & 0x0F;
			hworden = efuse_data & 0x0F;
			word_cnts = efuse_calculate_word_cnts(hworden);
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
		} else {
			continual = false;
		}
	}

	return efuse_addr;
}