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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9300_11NA_HT_DS_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NA_HT_SS_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NA_HT_TS_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NA_OFDM_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NG_HT_DS_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NG_HT_SS_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NG_HT_TS_SHIFT ; 
 int /*<<< orphan*/  AR9300_11NG_OFDM_SHIFT ; 
 scalar_t__ IS_CHAN_5GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT20 (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_init_txpower_cck (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar9003_hw_init_txpower_ht (struct ath_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ar9003_hw_init_txpower_ofdm (struct ath_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_init_txpower_stbc (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9003_hw_init_rate_txpower(struct ath_hw *ah, u8 *rate_array,
				 struct ath9k_channel *chan)
{
	if (IS_CHAN_5GHZ(chan)) {
		ar9003_hw_init_txpower_ofdm(ah, rate_array,
					    AR9300_11NA_OFDM_SHIFT);
		if (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) {
			ar9003_hw_init_txpower_ht(ah, rate_array,
						  AR9300_11NA_HT_SS_SHIFT,
						  AR9300_11NA_HT_DS_SHIFT,
						  AR9300_11NA_HT_TS_SHIFT,
						  IS_CHAN_HT40(chan));
			ar9003_hw_init_txpower_stbc(ah,
						    AR9300_11NA_HT_SS_SHIFT,
						    AR9300_11NA_HT_DS_SHIFT,
						    AR9300_11NA_HT_TS_SHIFT);
		}
	} else {
		ar9003_hw_init_txpower_cck(ah, rate_array);
		ar9003_hw_init_txpower_ofdm(ah, rate_array,
					    AR9300_11NG_OFDM_SHIFT);
		if (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) {
			ar9003_hw_init_txpower_ht(ah, rate_array,
						  AR9300_11NG_HT_SS_SHIFT,
						  AR9300_11NG_HT_DS_SHIFT,
						  AR9300_11NG_HT_TS_SHIFT,
						  IS_CHAN_HT40(chan));
			ar9003_hw_init_txpower_stbc(ah,
						    AR9300_11NG_HT_SS_SHIFT,
						    AR9300_11NG_HT_DS_SHIFT,
						    AR9300_11NG_HT_TS_SHIFT);
		}
	}
}