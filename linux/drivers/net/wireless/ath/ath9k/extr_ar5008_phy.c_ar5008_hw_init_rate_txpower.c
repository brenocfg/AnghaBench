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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR5008_11NA_HT_DS_SHIFT ; 
 int /*<<< orphan*/  AR5008_11NA_HT_SS_SHIFT ; 
 int /*<<< orphan*/  AR5008_11NA_OFDM_SHIFT ; 
 int /*<<< orphan*/  AR5008_11NG_HT_DS_SHIFT ; 
 int /*<<< orphan*/  AR5008_11NG_HT_SS_SHIFT ; 
 int /*<<< orphan*/  AR5008_11NG_OFDM_SHIFT ; 
 scalar_t__ IS_CHAN_5GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT20 (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar5008_hw_init_txpower_cck (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar5008_hw_init_txpower_ht (struct ath_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ar5008_hw_init_txpower_ofdm (struct ath_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ar5008_hw_init_rate_txpower(struct ath_hw *ah, int16_t *rate_array,
				 struct ath9k_channel *chan, int ht40_delta)
{
	if (IS_CHAN_5GHZ(chan)) {
		ar5008_hw_init_txpower_ofdm(ah, rate_array,
					    AR5008_11NA_OFDM_SHIFT);
		if (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) {
			ar5008_hw_init_txpower_ht(ah, rate_array,
						  AR5008_11NA_HT_SS_SHIFT,
						  AR5008_11NA_HT_DS_SHIFT,
						  IS_CHAN_HT40(chan),
						  ht40_delta);
		}
	} else {
		ar5008_hw_init_txpower_cck(ah, rate_array);
		ar5008_hw_init_txpower_ofdm(ah, rate_array,
					    AR5008_11NG_OFDM_SHIFT);
		if (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) {
			ar5008_hw_init_txpower_ht(ah, rate_array,
						  AR5008_11NG_HT_SS_SHIFT,
						  AR5008_11NG_HT_DS_SHIFT,
						  IS_CHAN_HT40(chan),
						  ht40_delta);
		}
	}
}