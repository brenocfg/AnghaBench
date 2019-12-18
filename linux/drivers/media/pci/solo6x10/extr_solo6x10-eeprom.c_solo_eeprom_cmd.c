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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int ADDR_LEN ; 
 int EE_DATA_WRITE ; 
 int EE_SHIFT_CLK ; 
 int SOLO_EEPROM_ACCESS_EN ; 
 int SOLO_EEPROM_ENABLE ; 
 int /*<<< orphan*/  solo_eeprom_reg_write (struct solo_dev*,int) ; 

__attribute__((used)) static void solo_eeprom_cmd(struct solo_dev *solo_dev, int cmd)
{
	int i;

	solo_eeprom_reg_write(solo_dev, SOLO_EEPROM_ACCESS_EN);
	solo_eeprom_reg_write(solo_dev, SOLO_EEPROM_ENABLE);

	for (i = 4 + ADDR_LEN; i >= 0; i--) {
		int dataval = (cmd & (1 << i)) ? EE_DATA_WRITE : 0;

		solo_eeprom_reg_write(solo_dev, SOLO_EEPROM_ENABLE | dataval);
		solo_eeprom_reg_write(solo_dev, SOLO_EEPROM_ENABLE |
				      EE_SHIFT_CLK | dataval);
	}

	solo_eeprom_reg_write(solo_dev, SOLO_EEPROM_ENABLE);
}