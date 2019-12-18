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
typedef  int /*<<< orphan*/  u16 ;
struct ar9287_eeprom {int dummy; } ;
struct TYPE_2__ {struct ar9287_eeprom map9287; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int AR9287_EEP_START_LOC ; 
 int SIZE_EEPROM_AR9287 ; 
 int /*<<< orphan*/  ath9k_hw_nvram_read (struct ath_hw*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __ath9k_hw_ar9287_fill_eeprom(struct ath_hw *ah)
{
	struct ar9287_eeprom *eep = &ah->eeprom.map9287;
	u16 *eep_data;
	int addr, eep_start_loc = AR9287_EEP_START_LOC;
	eep_data = (u16 *)eep;

	for (addr = 0; addr < SIZE_EEPROM_AR9287; addr++) {
		if (!ath9k_hw_nvram_read(ah, addr + eep_start_loc, eep_data))
			return false;
		eep_data++;
	}

	return true;
}