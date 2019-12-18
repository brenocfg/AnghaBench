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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 size_t ALL_TARGET_LEGACY_11L ; 
 size_t ALL_TARGET_LEGACY_11S ; 
 size_t ALL_TARGET_LEGACY_1L_5L ; 
 size_t ALL_TARGET_LEGACY_5S ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_11L ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_11S ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_1L_5L ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_5S ; 
 int /*<<< orphan*/  ar9003_hw_eeprom_get_cck_tgt_pwr (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_get_cck_target_powers(struct ath_hw *ah, u16 freq,
					    u8 *targetPowerValT2)
{
	targetPowerValT2[ALL_TARGET_LEGACY_1L_5L] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_1L_5L,
					     freq);
	targetPowerValT2[ALL_TARGET_LEGACY_5S] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_5S, freq);
	targetPowerValT2[ALL_TARGET_LEGACY_11L] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_11L, freq);
	targetPowerValT2[ALL_TARGET_LEGACY_11S] =
	    ar9003_hw_eeprom_get_cck_tgt_pwr(ah, LEGACY_TARGET_RATE_11S, freq);
}