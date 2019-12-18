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
typedef  int u8 ;
typedef  int u32 ;
struct rtl_sta_info {int wireless_mode; int ratr_index; } ;
struct rtl_phy {int /*<<< orphan*/  rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; } ;
struct TYPE_3__ {int* rx_mask; } ;
struct TYPE_4__ {int cap; TYPE_1__ mcs; } ;
struct ieee80211_sta {int aid; int* supp_rates; TYPE_2__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_RATR ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  H2C_8723B_RA_MASK ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int RATR_INX_WIRELESS_B ; 
 int RATR_INX_WIRELESS_GB ; 
 int RATR_INX_WIRELESS_NGB ; 
 int /*<<< orphan*/  RF_1T1R ; 
 int /*<<< orphan*/  RF_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
#define  WIRELESS_MODE_B 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 int _rtl8723be_mrate_idx_to_arfr_id (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  _rtl8723be_set_bcn_ctrl_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723be_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723be_update_hal_rate_mask(struct ieee80211_hw *hw,
					   struct ieee80211_sta *sta,
					   u8 rssi_level, bool update_bw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_sta_info *sta_entry = NULL;
	u32 ratr_bitmap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->ht_cap.cap &
			      IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
	u8 curshortgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 curshortgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	enum wireless_mode wirelessmode = 0;
	bool shortgi = false;
	u8 rate_mask[7];
	u8 macid = 0;

	sta_entry = (struct rtl_sta_info *)sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;
	if (mac->opmode == NL80211_IFTYPE_STATION ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT)
		curtxbw_40mhz = mac->bw_40;
	else if (mac->opmode == NL80211_IFTYPE_AP ||
		 mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

	ratr_bitmap = sta->supp_rates[0];

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_bitmap = 0xfff;

	ratr_bitmap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	switch (wirelessmode) {
	case WIRELESS_MODE_B:
		ratr_index = RATR_INX_WIRELESS_B;
		if (ratr_bitmap & 0x0000000c)
			ratr_bitmap &= 0x0000000d;
		else
			ratr_bitmap &= 0x0000000f;
		break;
	case WIRELESS_MODE_G:
		ratr_index = RATR_INX_WIRELESS_GB;

		if (rssi_level == 1)
			ratr_bitmap &= 0x00000f00;
		else if (rssi_level == 2)
			ratr_bitmap &= 0x00000ff0;
		else
			ratr_bitmap &= 0x00000ff5;
		break;
	case WIRELESS_MODE_N_24G:
	case WIRELESS_MODE_N_5G:
		ratr_index = RATR_INX_WIRELESS_NGB;
		if (rtlphy->rf_type == RF_1T1R) {
			if (curtxbw_40mhz) {
				if (rssi_level == 1)
					ratr_bitmap &= 0x000f0000;
				else if (rssi_level == 2)
					ratr_bitmap &= 0x000ff000;
				else
					ratr_bitmap &= 0x000ff015;
			} else {
				if (rssi_level == 1)
					ratr_bitmap &= 0x000f0000;
				else if (rssi_level == 2)
					ratr_bitmap &= 0x000ff000;
				else
					ratr_bitmap &= 0x000ff005;
			}
		} else {
			if (curtxbw_40mhz) {
				if (rssi_level == 1)
					ratr_bitmap &= 0x0f8f0000;
				else if (rssi_level == 2)
					ratr_bitmap &= 0x0f8ff000;
				else
					ratr_bitmap &= 0x0f8ff015;
			} else {
				if (rssi_level == 1)
					ratr_bitmap &= 0x0f8f0000;
				else if (rssi_level == 2)
					ratr_bitmap &= 0x0f8ff000;
				else
					ratr_bitmap &= 0x0f8ff005;
			}
		}
		if ((curtxbw_40mhz && curshortgi_40mhz) ||
		    (!curtxbw_40mhz && curshortgi_20mhz)) {
			if (macid == 0)
				shortgi = true;
			else if (macid == 1)
				shortgi = false;
		}
		break;
	default:
		ratr_index = RATR_INX_WIRELESS_NGB;

		if (rtlphy->rf_type == RF_1T2R)
			ratr_bitmap &= 0x000ff0ff;
		else
			ratr_bitmap &= 0x0f0ff0ff;
		break;
	}

	sta_entry->ratr_index = ratr_index;

	RT_TRACE(rtlpriv, COMP_RATR, DBG_DMESG,
		 "ratr_bitmap :%x\n", ratr_bitmap);
	*(u32 *)&rate_mask = (ratr_bitmap & 0x0fffffff) |
				       (ratr_index << 28);
	rate_mask[0] = macid;
	rate_mask[1] = _rtl8723be_mrate_idx_to_arfr_id(hw, ratr_index) |
						      (shortgi ? 0x80 : 0x00);
	rate_mask[2] = curtxbw_40mhz | ((!update_bw) << 3);

	rate_mask[3] = (u8)(ratr_bitmap & 0x000000ff);
	rate_mask[4] = (u8)((ratr_bitmap & 0x0000ff00) >> 8);
	rate_mask[5] = (u8)((ratr_bitmap & 0x00ff0000) >> 16);
	rate_mask[6] = (u8)((ratr_bitmap & 0xff000000) >> 24);

	RT_TRACE(rtlpriv, COMP_RATR, DBG_DMESG,
		 "Rate_index:%x, ratr_val:%x, %x:%x:%x:%x:%x:%x:%x\n",
		 ratr_index, ratr_bitmap,
		 rate_mask[0], rate_mask[1],
		 rate_mask[2], rate_mask[3],
		 rate_mask[4], rate_mask[5],
		 rate_mask[6]);
	rtl8723be_fill_h2c_cmd(hw, H2C_8723B_RA_MASK, 7, rate_mask);
	_rtl8723be_set_bcn_ctrl_reg(hw, BIT(3), 0);
}