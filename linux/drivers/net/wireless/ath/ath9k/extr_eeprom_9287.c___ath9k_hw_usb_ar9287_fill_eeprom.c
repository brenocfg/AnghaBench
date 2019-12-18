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
struct TYPE_2__ {int /*<<< orphan*/  map9287; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9287_HTC_EEP_START_LOC ; 
 int /*<<< orphan*/  SIZE_EEPROM_AR9287 ; 
 int /*<<< orphan*/  ath9k_hw_usb_gen_fill_eeprom (struct ath_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __ath9k_hw_usb_ar9287_fill_eeprom(struct ath_hw *ah)
{
	u16 *eep_data = (u16 *)&ah->eeprom.map9287;

	ath9k_hw_usb_gen_fill_eeprom(ah, eep_data,
				     AR9287_HTC_EEP_START_LOC,
				     SIZE_EEPROM_AR9287);
	return true;
}