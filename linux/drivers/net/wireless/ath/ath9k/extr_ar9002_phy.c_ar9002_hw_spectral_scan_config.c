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
typedef  int /*<<< orphan*/  u32 ;
struct ath_spec_scan {int count; int period; int fft_period; scalar_t__ endless; scalar_t__ short_repeat; int /*<<< orphan*/  enabled; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_FFT_ENA ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_COUNT ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_COUNT_KIWI ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_FFT_PERIOD ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_PERIOD ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_PHYERR_MASK_SELECT ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI ; 
 scalar_t__ AR_SREV_9280 (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9002_hw_spectral_scan_config(struct ath_hw *ah,
				    struct ath_spec_scan *param)
{
	u32 repeat_bit;
	u8 count;

	if (!param->enabled) {
		REG_CLR_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_ENABLE);
		return;
	}
	REG_SET_BIT(ah, AR_PHY_RADAR_0, AR_PHY_RADAR_0_FFT_ENA);
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, AR_PHY_SPECTRAL_SCAN_ENABLE);

	if (AR_SREV_9280(ah))
		repeat_bit = AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT;
	else
		repeat_bit = AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI;

	if (param->short_repeat)
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, repeat_bit);
	else
		REG_CLR_BIT(ah, AR_PHY_SPECTRAL_SCAN, repeat_bit);

	/* on AR92xx, the highest bit of count will make the the chip send
	 * spectral samples endlessly. Check if this really was intended,
	 * and fix otherwise.
	 */
	count = param->count;
	if (param->endless) {
		if (AR_SREV_9280(ah))
			count = 0x80;
		else
			count = 0;
	} else if (count & 0x80)
		count = 0x7f;
	else if (!count)
		count = 1;

	if (AR_SREV_9280(ah)) {
		REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
			      AR_PHY_SPECTRAL_SCAN_COUNT, count);
	} else {
		REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
			      AR_PHY_SPECTRAL_SCAN_COUNT_KIWI, count);
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_PHYERR_MASK_SELECT);
	}

	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_PERIOD, param->period);
	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_FFT_PERIOD, param->fft_period);

	return;
}