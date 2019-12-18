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
struct ath_nf_limits {scalar_t__ max; } ;
struct ath_hw {int rxchainmask; int /*<<< orphan*/  curchan; } ;
struct ath_common {int dummy; } ;
struct ath9k_nfcal_hist {size_t currIndex; scalar_t__ invalidNFcount; scalar_t__ privNF; void** nfCalBuffer; } ;
struct ath9k_hw_cal_data {int /*<<< orphan*/  cal_flags; struct ath9k_nfcal_hist* nfCalHist; } ;
typedef  void* int16_t ;

/* Variables and functions */
 int AR5416_MAX_CHAINS ; 
 size_t ATH9K_NF_CAL_HIST_MAX ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int /*<<< orphan*/  IS_CHAN_HT40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFCAL_INTF ; 
 int NUM_NF_READINGS ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_get_nf_hist_mid (void**) ; 
 struct ath_nf_limits* ath9k_hw_get_nf_limits (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_hw_update_nfcal_hist_buffer(struct ath_hw *ah,
					      struct ath9k_hw_cal_data *cal,
					      int16_t *nfarray)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_nf_limits *limit;
	struct ath9k_nfcal_hist *h;
	bool high_nf_mid = false;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	int i;

	h = cal->nfCalHist;
	limit = ath9k_hw_get_nf_limits(ah, ah->curchan);

	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (!(chainmask & (1 << i)) ||
		    ((i >= AR5416_MAX_CHAINS) && !IS_CHAN_HT40(ah->curchan)))
			continue;

		h[i].nfCalBuffer[h[i].currIndex] = nfarray[i];

		if (++h[i].currIndex >= ATH9K_NF_CAL_HIST_MAX)
			h[i].currIndex = 0;

		if (h[i].invalidNFcount > 0) {
			h[i].invalidNFcount--;
			h[i].privNF = nfarray[i];
		} else {
			h[i].privNF =
				ath9k_hw_get_nf_hist_mid(h[i].nfCalBuffer);
		}

		if (!h[i].privNF)
			continue;

		if (h[i].privNF > limit->max) {
			high_nf_mid = true;

			ath_dbg(common, CALIBRATE,
				"NFmid[%d] (%d) > MAX (%d), %s\n",
				i, h[i].privNF, limit->max,
				(test_bit(NFCAL_INTF, &cal->cal_flags) ?
				 "not corrected (due to interference)" :
				 "correcting to MAX"));

			/*
			 * Normally we limit the average noise floor by the
			 * hardware specific maximum here. However if we have
			 * encountered stuck beacons because of interference,
			 * we bypass this limit here in order to better deal
			 * with our environment.
			 */
			if (!test_bit(NFCAL_INTF, &cal->cal_flags))
				h[i].privNF = limit->max;
		}
	}

	/*
	 * If the noise floor seems normal for all chains, assume that
	 * there is no significant interference in the environment anymore.
	 * Re-enable the enforcement of the NF maximum again.
	 */
	if (!high_nf_mid)
		clear_bit(NFCAL_INTF, &cal->cal_flags);
}