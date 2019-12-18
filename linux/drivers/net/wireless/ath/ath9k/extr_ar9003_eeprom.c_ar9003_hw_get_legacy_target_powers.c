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
 size_t ALL_TARGET_LEGACY_36 ; 
 size_t ALL_TARGET_LEGACY_48 ; 
 size_t ALL_TARGET_LEGACY_54 ; 
 size_t ALL_TARGET_LEGACY_6_24 ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_36 ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_48 ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_54 ; 
 int /*<<< orphan*/  LEGACY_TARGET_RATE_6_24 ; 
 int /*<<< orphan*/  ar9003_hw_eeprom_get_tgt_pwr (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9003_hw_get_legacy_target_powers(struct ath_hw *ah, u16 freq,
					       u8 *targetPowerValT2,
					       bool is2GHz)
{
	targetPowerValT2[ALL_TARGET_LEGACY_6_24] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_6_24, freq,
					 is2GHz);
	targetPowerValT2[ALL_TARGET_LEGACY_36] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_36, freq,
					 is2GHz);
	targetPowerValT2[ALL_TARGET_LEGACY_48] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_48, freq,
					 is2GHz);
	targetPowerValT2[ALL_TARGET_LEGACY_54] =
	    ar9003_hw_eeprom_get_tgt_pwr(ah, LEGACY_TARGET_RATE_54, freq,
					 is2GHz);
}