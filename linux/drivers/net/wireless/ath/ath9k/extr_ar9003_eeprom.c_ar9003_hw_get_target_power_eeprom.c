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
struct ath_common {int dummy; } ;
struct ath9k_channel {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REGULATORY ; 
 int /*<<< orphan*/  ar9003_hw_get_cck_target_powers (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar9003_hw_get_ht20_target_powers (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar9003_hw_get_ht40_target_powers (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar9003_hw_get_legacy_target_powers (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 unsigned int ar9300RateSize ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_get_target_power_eeprom(struct ath_hw *ah,
					      struct ath9k_channel *chan,
					      u8 *targetPowerValT2)
{
	bool is2GHz = IS_CHAN_2GHZ(chan);
	unsigned int i = 0;
	struct ath_common *common = ath9k_hw_common(ah);
	u16 freq = chan->channel;

	if (is2GHz)
		ar9003_hw_get_cck_target_powers(ah, freq, targetPowerValT2);

	ar9003_hw_get_legacy_target_powers(ah, freq, targetPowerValT2, is2GHz);
	ar9003_hw_get_ht20_target_powers(ah, freq, targetPowerValT2, is2GHz);

	if (IS_CHAN_HT40(chan))
		ar9003_hw_get_ht40_target_powers(ah, freq, targetPowerValT2,
						 is2GHz);

	for (i = 0; i < ar9300RateSize; i++) {
		ath_dbg(common, REGULATORY, "TPC[%02d] 0x%08x\n",
			i, targetPowerValT2[i]);
	}
}