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
struct ath_hw {int /*<<< orphan*/  paprd_target_power; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int ALL_TARGET_HT20_0_8_16 ; 
 int ALL_TARGET_HT20_7 ; 
 int ALL_TARGET_HT40_0_8_16 ; 
 int ALL_TARGET_HT40_7 ; 
 int /*<<< orphan*/  AR_SREV_9330 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9340 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9462 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9565 (struct ath_hw*) ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_is_paprd_enabled (struct ath_hw*) ; 

__attribute__((used)) static void ar9003_paprd_set_txpower(struct ath_hw *ah,
				     struct ath9k_channel *chan,
				     u8 *targetPowerValT2)
{
	int i;

	if (!ar9003_is_paprd_enabled(ah))
		return;

	if (IS_CHAN_HT40(chan))
		i = ALL_TARGET_HT40_7;
	else
		i = ALL_TARGET_HT20_7;

	if (IS_CHAN_2GHZ(chan)) {
		if (!AR_SREV_9330(ah) && !AR_SREV_9340(ah) &&
		    !AR_SREV_9462(ah) && !AR_SREV_9565(ah)) {
			if (IS_CHAN_HT40(chan))
				i = ALL_TARGET_HT40_0_8_16;
			else
				i = ALL_TARGET_HT20_0_8_16;
		}
	}

	ah->paprd_target_power = targetPowerValT2[i];
}