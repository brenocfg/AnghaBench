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
struct ath_hw {TYPE_1__* caldata; } ;
struct ath9k_nfcal_hist {int /*<<< orphan*/  privNF; int /*<<< orphan*/ * nfCalBuffer; int /*<<< orphan*/  invalidNFcount; scalar_t__ currIndex; } ;
struct ath9k_channel {int /*<<< orphan*/  channelFlags; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {struct ath9k_nfcal_hist* nfCalHist; int /*<<< orphan*/  channelFlags; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int AR5416_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_CCA_FILTERWINDOW_LENGTH ; 
 int ATH9K_NF_CAL_HIST_MAX ; 
 int NUM_NF_READINGS ; 
 int /*<<< orphan*/  ath9k_hw_get_default_nf (struct ath_hw*,struct ath9k_channel*,int) ; 

void ath9k_init_nfcal_hist_buffer(struct ath_hw *ah,
				  struct ath9k_channel *chan)
{
	struct ath9k_nfcal_hist *h;
	int i, j, k = 0;

	ah->caldata->channel = chan->channel;
	ah->caldata->channelFlags = chan->channelFlags;
	h = ah->caldata->nfCalHist;
	for (i = 0; i < NUM_NF_READINGS; i++) {
		h[i].currIndex = 0;
		h[i].privNF = ath9k_hw_get_default_nf(ah, chan, k);
		h[i].invalidNFcount = AR_PHY_CCA_FILTERWINDOW_LENGTH;
		for (j = 0; j < ATH9K_NF_CAL_HIST_MAX; j++)
			h[i].nfCalBuffer[j] = h[i].privNF;
		if (++k >= AR5416_MAX_CHAINS)
			k = 0;
	}
}