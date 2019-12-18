#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {scalar_t__ txgi_factor; } ;
struct TYPE_4__ {scalar_t__ bw20; scalar_t__ bw40; } ;
struct TYPE_3__ {scalar_t__ ofdm; scalar_t__ bw20; } ;
struct rtw_2g_txpwr_idx {scalar_t__* cck_base; scalar_t__* bw40_base; TYPE_2__ ht_2s_diff; TYPE_1__ ht_1s_diff; } ;
typedef  enum rtw_bandwidth { ____Placeholder_rtw_bandwidth } rtw_bandwidth ;

/* Variables and functions */
 scalar_t__ DESC_RATE11M ; 
 scalar_t__ DESC_RATE54M ; 
 scalar_t__ DESC_RATE6M ; 
 scalar_t__ DESC_RATEMCS0 ; 
 scalar_t__ DESC_RATEMCS15 ; 
 scalar_t__ DESC_RATEMCS8 ; 
 scalar_t__ DESC_RATEVHT1SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS9 ; 
#define  RTW_CHANNEL_WIDTH_20 129 
#define  RTW_CHANNEL_WIDTH_40 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u8 rtw_phy_get_2g_tx_power_index(struct rtw_dev *rtwdev,
					struct rtw_2g_txpwr_idx *pwr_idx_2g,
					enum rtw_bandwidth bandwidth,
					u8 rate, u8 group)
{
	struct rtw_chip_info *chip = rtwdev->chip;
	u8 tx_power;
	bool mcs_rate;
	bool above_2ss;
	u8 factor = chip->txgi_factor;

	if (rate <= DESC_RATE11M)
		tx_power = pwr_idx_2g->cck_base[group];
	else
		tx_power = pwr_idx_2g->bw40_base[group];

	if (rate >= DESC_RATE6M && rate <= DESC_RATE54M)
		tx_power += pwr_idx_2g->ht_1s_diff.ofdm * factor;

	mcs_rate = (rate >= DESC_RATEMCS0 && rate <= DESC_RATEMCS15) ||
		   (rate >= DESC_RATEVHT1SS_MCS0 &&
		    rate <= DESC_RATEVHT2SS_MCS9);
	above_2ss = (rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
		    (rate >= DESC_RATEVHT2SS_MCS0);

	if (!mcs_rate)
		return tx_power;

	switch (bandwidth) {
	default:
		WARN_ON(1);
		/* fall through */
	case RTW_CHANNEL_WIDTH_20:
		tx_power += pwr_idx_2g->ht_1s_diff.bw20 * factor;
		if (above_2ss)
			tx_power += pwr_idx_2g->ht_2s_diff.bw20 * factor;
		break;
	case RTW_CHANNEL_WIDTH_40:
		/* bw40 is the base power */
		if (above_2ss)
			tx_power += pwr_idx_2g->ht_2s_diff.bw40 * factor;
		break;
	}

	return tx_power;
}