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
typedef  int u16 ;
struct ath5k_eeprom_info {scalar_t__ ee_version; } ;

/* Variables and functions */
 int AR5K_EEPROM_CHANNEL_DIS ; 
 unsigned int AR5K_EEPROM_MODE_11A ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_2 ; 

__attribute__((used)) static u16 ath5k_eeprom_bin2freq(struct ath5k_eeprom_info *ee, u16 bin,
							unsigned int mode)
{
	u16 val;

	if (bin == AR5K_EEPROM_CHANNEL_DIS)
		return bin;

	if (mode == AR5K_EEPROM_MODE_11A) {
		if (ee->ee_version > AR5K_EEPROM_VERSION_3_2)
			val = (5 * bin) + 4800;
		else
			val = bin > 62 ? (10 * 62) + (5 * (bin - 62)) + 5100 :
				(bin * 10) + 5100;
	} else {
		if (ee->ee_version > AR5K_EEPROM_VERSION_3_2)
			val = bin + 2300;
		else
			val = bin + 2400;
	}

	return val;
}