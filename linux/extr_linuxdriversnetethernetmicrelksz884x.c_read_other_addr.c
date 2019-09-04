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
typedef  void* u8 ;
typedef  int u16 ;
struct ksz_switch {void** other_addr; } ;
struct ksz_hw {struct ksz_switch* ksz_switch; } ;

/* Variables and functions */
 scalar_t__ EEPROM_DATA_OTHER_MAC_ADDR ; 
 int eeprom_read (struct ksz_hw*,scalar_t__) ; 

__attribute__((used)) static void read_other_addr(struct ksz_hw *hw)
{
	int i;
	u16 data[3];
	struct ksz_switch *sw = hw->ksz_switch;

	for (i = 0; i < 3; i++)
		data[i] = eeprom_read(hw, i + EEPROM_DATA_OTHER_MAC_ADDR);
	if ((data[0] || data[1] || data[2]) && data[0] != 0xffff) {
		sw->other_addr[5] = (u8) data[0];
		sw->other_addr[4] = (u8)(data[0] >> 8);
		sw->other_addr[3] = (u8) data[1];
		sw->other_addr[2] = (u8)(data[1] >> 8);
		sw->other_addr[1] = (u8) data[2];
		sw->other_addr[0] = (u8)(data[2] >> 8);
	}
}