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
struct rtl_phy {int**** tx_power_by_rate_offset; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
typedef  enum band_type { ____Placeholder_band_type } band_type ;

/* Variables and functions */
#define  DESC92C_RATE11M 155 
#define  DESC92C_RATE12M 154 
#define  DESC92C_RATE18M 153 
#define  DESC92C_RATE1M 152 
#define  DESC92C_RATE24M 151 
#define  DESC92C_RATE2M 150 
#define  DESC92C_RATE36M 149 
#define  DESC92C_RATE48M 148 
#define  DESC92C_RATE54M 147 
#define  DESC92C_RATE5_5M 146 
#define  DESC92C_RATE6M 145 
#define  DESC92C_RATE9M 144 
#define  DESC92C_RATEMCS0 143 
#define  DESC92C_RATEMCS1 142 
#define  DESC92C_RATEMCS10 141 
#define  DESC92C_RATEMCS11 140 
#define  DESC92C_RATEMCS12 139 
#define  DESC92C_RATEMCS13 138 
#define  DESC92C_RATEMCS14 137 
#define  DESC92C_RATEMCS15 136 
#define  DESC92C_RATEMCS2 135 
#define  DESC92C_RATEMCS3 134 
#define  DESC92C_RATEMCS4 133 
#define  DESC92C_RATEMCS5 132 
#define  DESC92C_RATEMCS6 131 
#define  DESC92C_RATEMCS7 130 
#define  DESC92C_RATEMCS8 129 
#define  DESC92C_RATEMCS9 128 
 int RF_1TX ; 
 int RF_2TX ; 
 int RF_TX_NUM_NONIMPLEMENT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int _rtl8723be_phy_get_ratesection_intxpower_byrate (int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl8723be_get_txpower_by_rate(struct ieee80211_hw *hw,
					 enum band_type band,
					 enum radio_path rfpath, u8 rate)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 shift = 0, rate_section, tx_num;
	s8 tx_pwr_diff = 0;

	rate_section = _rtl8723be_phy_get_ratesection_intxpower_byrate(rfpath,
								       rate);
	tx_num = RF_TX_NUM_NONIMPLEMENT;

	if (tx_num == RF_TX_NUM_NONIMPLEMENT) {
		if (rate >= DESC92C_RATEMCS8 && rate <= DESC92C_RATEMCS15)
			tx_num = RF_2TX;
		else
			tx_num = RF_1TX;
	}

	switch (rate) {
	case DESC92C_RATE6M:
	case DESC92C_RATE24M:
	case DESC92C_RATEMCS0:
	case DESC92C_RATEMCS4:
	case DESC92C_RATEMCS8:
	case DESC92C_RATEMCS12:
		shift = 0;
		break;
	case DESC92C_RATE1M:
	case DESC92C_RATE2M:
	case DESC92C_RATE9M:
	case DESC92C_RATE36M:
	case DESC92C_RATEMCS1:
	case DESC92C_RATEMCS5:
	case DESC92C_RATEMCS9:
	case DESC92C_RATEMCS13:
		shift = 8;
		break;
	case DESC92C_RATE5_5M:
	case DESC92C_RATE12M:
	case DESC92C_RATE48M:
	case DESC92C_RATEMCS2:
	case DESC92C_RATEMCS6:
	case DESC92C_RATEMCS10:
	case DESC92C_RATEMCS14:
		shift = 16;
		break;
	case DESC92C_RATE11M:
	case DESC92C_RATE18M:
	case DESC92C_RATE54M:
	case DESC92C_RATEMCS3:
	case DESC92C_RATEMCS7:
	case DESC92C_RATEMCS11:
	case DESC92C_RATEMCS15:
		shift = 24;
		break;
	default:
		WARN_ONCE(true, "rtl8723be: Rate_Section is Illegal\n");
		break;
	}
	tx_pwr_diff = (u8)(rtlphy->tx_power_by_rate_offset[band][rfpath][tx_num]
					  [rate_section] >> shift) & 0xff;

	return	tx_pwr_diff;
}