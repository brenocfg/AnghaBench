#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {size_t txgi_factor; } ;
struct TYPE_8__ {size_t bw80; } ;
struct TYPE_7__ {size_t bw80; } ;
struct TYPE_6__ {size_t bw20; size_t bw40; } ;
struct TYPE_5__ {size_t ofdm; size_t bw20; } ;
struct rtw_5g_txpwr_idx {size_t* bw40_base; TYPE_4__ vht_2s_diff; TYPE_3__ vht_1s_diff; TYPE_2__ ht_2s_diff; TYPE_1__ ht_1s_diff; } ;
typedef  enum rtw_bandwidth { ____Placeholder_rtw_bandwidth } rtw_bandwidth ;

/* Variables and functions */
 size_t DESC_RATEMCS0 ; 
 size_t DESC_RATEMCS15 ; 
 size_t DESC_RATEMCS8 ; 
 size_t DESC_RATEVHT1SS_MCS0 ; 
 size_t DESC_RATEVHT2SS_MCS0 ; 
 size_t DESC_RATEVHT2SS_MCS9 ; 
#define  RTW_CHANNEL_WIDTH_20 130 
#define  RTW_CHANNEL_WIDTH_40 129 
#define  RTW_CHANNEL_WIDTH_80 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u8 rtw_phy_get_5g_tx_power_index(struct rtw_dev *rtwdev,
					struct rtw_5g_txpwr_idx *pwr_idx_5g,
					enum rtw_bandwidth bandwidth,
					u8 rate, u8 group)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 tx_power;
	u8 upper, lower;
	bool mcs_rate;
	bool above_2ss;
	u8 factor = chip->txgi_factor;

	tx_power = pwr_idx_5g->bw40_base[group];

	mcs_rate = (rate >= DESC_RATEMCS0 && rate <= DESC_RATEMCS15) ||
		   (rate >= DESC_RATEVHT1SS_MCS0 &&
		    rate <= DESC_RATEVHT2SS_MCS9);
	above_2ss = (rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
		    (rate >= DESC_RATEVHT2SS_MCS0);

	if (!mcs_rate) {
		tx_power += pwr_idx_5g->ht_1s_diff.ofdm * factor;
		return tx_power;
	}

	switch (bandwidth) {
	default:
		WARN_ON(1);
		/* fall through */
	case RTW_CHANNEL_WIDTH_20:
		tx_power += pwr_idx_5g->ht_1s_diff.bw20 * factor;
		if (above_2ss)
			tx_power += pwr_idx_5g->ht_2s_diff.bw20 * factor;
		break;
	case RTW_CHANNEL_WIDTH_40:
		/* bw40 is the base power */
		if (above_2ss)
			tx_power += pwr_idx_5g->ht_2s_diff.bw40 * factor;
		break;
	case RTW_CHANNEL_WIDTH_80:
		/* the base idx of bw80 is the average of bw40+/bw40- */
		lower = pwr_idx_5g->bw40_base[group];
		upper = pwr_idx_5g->bw40_base[group + 1];

		tx_power = (lower + upper) / 2;
		tx_power += pwr_idx_5g->vht_1s_diff.bw80 * factor;
		if (above_2ss)
			tx_power += pwr_idx_5g->vht_2s_diff.bw80 * factor;
		break;
	}

	return tx_power;
}