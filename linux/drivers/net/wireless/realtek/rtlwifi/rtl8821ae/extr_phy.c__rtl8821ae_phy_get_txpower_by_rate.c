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
typedef  int u8 ;
struct TYPE_2__ {int eeprom_regulatory; } ;
struct rtl_phy {int**** tx_power_by_rate_offset; int /*<<< orphan*/  current_channel; int /*<<< orphan*/  current_chan_bw; } ;
struct rtl_priv {TYPE_1__ efuse; struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DESC_RATE11M 175 
#define  DESC_RATE12M 174 
#define  DESC_RATE18M 173 
#define  DESC_RATE1M 172 
#define  DESC_RATE24M 171 
#define  DESC_RATE2M 170 
#define  DESC_RATE36M 169 
#define  DESC_RATE48M 168 
#define  DESC_RATE54M 167 
#define  DESC_RATE5_5M 166 
#define  DESC_RATE6M 165 
#define  DESC_RATE9M 164 
#define  DESC_RATEMCS0 163 
#define  DESC_RATEMCS1 162 
#define  DESC_RATEMCS10 161 
#define  DESC_RATEMCS11 160 
#define  DESC_RATEMCS12 159 
#define  DESC_RATEMCS13 158 
#define  DESC_RATEMCS14 157 
#define  DESC_RATEMCS15 156 
#define  DESC_RATEMCS2 155 
#define  DESC_RATEMCS3 154 
#define  DESC_RATEMCS4 153 
#define  DESC_RATEMCS5 152 
#define  DESC_RATEMCS6 151 
#define  DESC_RATEMCS7 150 
#define  DESC_RATEMCS8 149 
#define  DESC_RATEMCS9 148 
#define  DESC_RATEVHT1SS_MCS0 147 
#define  DESC_RATEVHT1SS_MCS1 146 
#define  DESC_RATEVHT1SS_MCS2 145 
#define  DESC_RATEVHT1SS_MCS3 144 
#define  DESC_RATEVHT1SS_MCS4 143 
#define  DESC_RATEVHT1SS_MCS5 142 
#define  DESC_RATEVHT1SS_MCS6 141 
#define  DESC_RATEVHT1SS_MCS7 140 
#define  DESC_RATEVHT1SS_MCS8 139 
#define  DESC_RATEVHT1SS_MCS9 138 
#define  DESC_RATEVHT2SS_MCS0 137 
#define  DESC_RATEVHT2SS_MCS1 136 
#define  DESC_RATEVHT2SS_MCS2 135 
#define  DESC_RATEVHT2SS_MCS3 134 
#define  DESC_RATEVHT2SS_MCS4 133 
#define  DESC_RATEVHT2SS_MCS5 132 
#define  DESC_RATEVHT2SS_MCS6 131 
#define  DESC_RATEVHT2SS_MCS7 130 
#define  DESC_RATEVHT2SS_MCS8 129 
#define  DESC_RATEVHT2SS_MCS9 128 
 int RF_1TX ; 
 int RF_2TX ; 
 int RF_TX_NUM_NONIMPLEMENT ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int _rtl8812ae_phy_get_txpower_limit (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int _rtl8821ae_phy_get_ratesection_intxpower_byrate (int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static s8 _rtl8821ae_phy_get_txpower_by_rate(struct ieee80211_hw *hw,
					u8 band, u8 path, u8 rate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 shift = 0, rate_section, tx_num;
	s8 tx_pwr_diff = 0;
	s8 limit = 0;

	rate_section = _rtl8821ae_phy_get_ratesection_intxpower_byrate(path, rate);
	tx_num = RF_TX_NUM_NONIMPLEMENT;

	if (tx_num == RF_TX_NUM_NONIMPLEMENT) {
		if ((rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
			(rate >= DESC_RATEVHT2SS_MCS2 && rate <= DESC_RATEVHT2SS_MCS9))
			tx_num = RF_2TX;
		else
			tx_num = RF_1TX;
	}

	switch (rate) {
	case DESC_RATE1M:
	case DESC_RATE6M:
	case DESC_RATE24M:
	case DESC_RATEMCS0:
	case DESC_RATEMCS4:
	case DESC_RATEMCS8:
	case DESC_RATEMCS12:
	case DESC_RATEVHT1SS_MCS0:
	case DESC_RATEVHT1SS_MCS4:
	case DESC_RATEVHT1SS_MCS8:
	case DESC_RATEVHT2SS_MCS2:
	case DESC_RATEVHT2SS_MCS6:
		shift = 0;
		break;
	case DESC_RATE2M:
	case DESC_RATE9M:
	case DESC_RATE36M:
	case DESC_RATEMCS1:
	case DESC_RATEMCS5:
	case DESC_RATEMCS9:
	case DESC_RATEMCS13:
	case DESC_RATEVHT1SS_MCS1:
	case DESC_RATEVHT1SS_MCS5:
	case DESC_RATEVHT1SS_MCS9:
	case DESC_RATEVHT2SS_MCS3:
	case DESC_RATEVHT2SS_MCS7:
		shift = 8;
		break;
	case DESC_RATE5_5M:
	case DESC_RATE12M:
	case DESC_RATE48M:
	case DESC_RATEMCS2:
	case DESC_RATEMCS6:
	case DESC_RATEMCS10:
	case DESC_RATEMCS14:
	case DESC_RATEVHT1SS_MCS2:
	case DESC_RATEVHT1SS_MCS6:
	case DESC_RATEVHT2SS_MCS0:
	case DESC_RATEVHT2SS_MCS4:
	case DESC_RATEVHT2SS_MCS8:
		shift = 16;
		break;
	case DESC_RATE11M:
	case DESC_RATE18M:
	case DESC_RATE54M:
	case DESC_RATEMCS3:
	case DESC_RATEMCS7:
	case DESC_RATEMCS11:
	case DESC_RATEMCS15:
	case DESC_RATEVHT1SS_MCS3:
	case DESC_RATEVHT1SS_MCS7:
	case DESC_RATEVHT2SS_MCS1:
	case DESC_RATEVHT2SS_MCS5:
	case DESC_RATEVHT2SS_MCS9:
		shift = 24;
		break;
	default:
		WARN_ONCE(true, "rtl8821ae: Rate_Section is Illegal\n");
		break;
	}

	tx_pwr_diff = (u8)(rtlphy->tx_power_by_rate_offset[band][path]
		[tx_num][rate_section] >> shift) & 0xff;

	/* RegEnableTxPowerLimit == 1 for 8812a & 8821a */
	if (rtlpriv->efuse.eeprom_regulatory != 2) {
		limit = _rtl8812ae_phy_get_txpower_limit(hw, band,
			rtlphy->current_chan_bw, path, rate,
			rtlphy->current_channel);

		if (rate == DESC_RATEVHT1SS_MCS8 || rate == DESC_RATEVHT1SS_MCS9  ||
			 rate == DESC_RATEVHT2SS_MCS8 || rate == DESC_RATEVHT2SS_MCS9) {
			if (limit < 0) {
				if (tx_pwr_diff < (-limit))
					tx_pwr_diff = -limit;
			}
		} else {
			if (limit < 0)
				tx_pwr_diff = limit;
			else
				tx_pwr_diff = tx_pwr_diff > limit ? limit : tx_pwr_diff;
		}
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Maximum power by rate %d, final power by rate %d\n",
			limit, tx_pwr_diff);
	}

	return	tx_pwr_diff;
}