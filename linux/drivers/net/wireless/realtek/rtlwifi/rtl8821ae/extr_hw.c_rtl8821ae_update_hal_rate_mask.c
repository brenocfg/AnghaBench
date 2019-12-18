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
typedef  int u8 ;
typedef  int u32 ;
struct rtl_sta_info {int wireless_mode; int ratr_index; } ;
struct rtl_phy {int current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_mcs_map; } ;
struct TYPE_8__ {TYPE_3__ vht_mcs; } ;
struct TYPE_5__ {int* rx_mask; } ;
struct TYPE_6__ {int cap; TYPE_1__ mcs; } ;
struct ieee80211_sta {int aid; int* supp_rates; TYPE_4__ vht_cap; TYPE_2__ ht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_RATR ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  H2C_8821AE_RA_MASK ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_SMPS_DYNAMIC ; 
 int IEEE80211_SMPS_OFF ; 
 int IEEE80211_SMPS_STATIC ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int RATR_INX_WIRELESS_AC_24N ; 
 int RATR_INX_WIRELESS_AC_5N ; 
 int RATR_INX_WIRELESS_B ; 
 int RATR_INX_WIRELESS_G ; 
 int RATR_INX_WIRELESS_GB ; 
 int RATR_INX_WIRELESS_NG ; 
 int RATR_INX_WIRELESS_NGB ; 
 int RF_1T1R ; 
 int RF_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
#define  WIRELESS_MODE_A 134 
#define  WIRELESS_MODE_AC_24G 133 
#define  WIRELESS_MODE_AC_5G 132 
 int WIRELESS_MODE_AC_ONLY ; 
#define  WIRELESS_MODE_B 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 int _rtl8821ae_get_ra_ldpc (struct ieee80211_hw*,int,struct rtl_sta_info*,int) ; 
 int _rtl8821ae_get_ra_rftype (struct ieee80211_hw*,int,int) ; 
 int _rtl8821ae_get_ra_shortgi (struct ieee80211_hw*,struct ieee80211_sta*,int) ; 
 int _rtl8821ae_get_vht_eni (int,int) ; 
 int _rtl8821ae_rate_to_bitmap_2ssvht (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl8821ae_set_bcn_ctrl_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _rtl8821ae_set_ra_vht_ratr_bitmap (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8821ae_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 int rtl_mrate_idx_to_arfr_id (struct ieee80211_hw*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8821ae_update_hal_rate_mask(struct ieee80211_hw *hw,
		struct ieee80211_sta *sta, u8 rssi_level, bool update_bw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_sta_info *sta_entry = NULL;
	u32 ratr_bitmap;
	u8 ratr_index;
	enum wireless_mode wirelessmode = 0;
	u8 curtxbw_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40)
				? 1 : 0;
	bool b_shortgi = false;
	u8 rate_mask[7];
	u8 macid = 0;
	u8 mimo_ps = IEEE80211_SMPS_OFF;
	u8 rf_type;

	sta_entry = (struct rtl_sta_info *)sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;

	RT_TRACE(rtlpriv, COMP_RATR, DBG_LOUD,
		 "wireless mode = 0x%x\n", wirelessmode);
	if (mac->opmode == NL80211_IFTYPE_STATION ||
		mac->opmode == NL80211_IFTYPE_MESH_POINT) {
		curtxbw_40mhz = mac->bw_40;
	} else if (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;
	if (wirelessmode == WIRELESS_MODE_N_5G ||
	    wirelessmode == WIRELESS_MODE_AC_5G ||
	    wirelessmode == WIRELESS_MODE_A)
		ratr_bitmap = sta->supp_rates[NL80211_BAND_5GHZ] << 4;
	else
		ratr_bitmap = sta->supp_rates[NL80211_BAND_2GHZ];

	if (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_bitmap = 0xfff;

	if (wirelessmode == WIRELESS_MODE_N_24G
		|| wirelessmode == WIRELESS_MODE_N_5G)
		ratr_bitmap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
				sta->ht_cap.mcs.rx_mask[0] << 12);
	else if (wirelessmode == WIRELESS_MODE_AC_24G
		|| wirelessmode == WIRELESS_MODE_AC_5G
		|| wirelessmode == WIRELESS_MODE_AC_ONLY)
		ratr_bitmap |= _rtl8821ae_rate_to_bitmap_2ssvht(
				sta->vht_cap.vht_mcs.rx_mcs_map) << 12;

	b_shortgi = _rtl8821ae_get_ra_shortgi(hw, sta, macid);
	rf_type = _rtl8821ae_get_ra_rftype(hw, wirelessmode, ratr_bitmap);

/*mac id owner*/
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
	case WIRELESS_MODE_A:
		ratr_index = RATR_INX_WIRELESS_G;
		ratr_bitmap &= 0x00000ff0;
		break;
	case WIRELESS_MODE_N_24G:
	case WIRELESS_MODE_N_5G:
		if (wirelessmode == WIRELESS_MODE_N_24G)
			ratr_index = RATR_INX_WIRELESS_NGB;
		else
			ratr_index = RATR_INX_WIRELESS_NG;

		if (mimo_ps == IEEE80211_SMPS_STATIC
			|| mimo_ps == IEEE80211_SMPS_DYNAMIC) {
			if (rssi_level == 1)
				ratr_bitmap &= 0x000f0000;
			else if (rssi_level == 2)
				ratr_bitmap &= 0x000ff000;
			else
				ratr_bitmap &= 0x000ff005;
		} else {
			if (rf_type == RF_1T1R) {
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
						ratr_bitmap &= 0x0fff0000;
					else if (rssi_level == 2)
						ratr_bitmap &= 0x0ffff000;
					else
						ratr_bitmap &= 0x0ffff015;
				} else {
					if (rssi_level == 1)
						ratr_bitmap &= 0x0fff0000;
					else if (rssi_level == 2)
						ratr_bitmap &= 0x0ffff000;
					else
						ratr_bitmap &= 0x0ffff005;
				}
			}
		}
		break;

	case WIRELESS_MODE_AC_24G:
		ratr_index = RATR_INX_WIRELESS_AC_24N;
		if (rssi_level == 1)
			ratr_bitmap &= 0xfc3f0000;
		else if (rssi_level == 2)
			ratr_bitmap &= 0xfffff000;
		else
			ratr_bitmap &= 0xffffffff;
		break;

	case WIRELESS_MODE_AC_5G:
		ratr_index = RATR_INX_WIRELESS_AC_5N;

		if (rf_type == RF_1T1R) {
			if (rssi_level == 1)	/*add by Gary for ac-series*/
				ratr_bitmap &= 0x003f8000;
			else if (rssi_level == 2)
				ratr_bitmap &= 0x003ff000;
			else
				ratr_bitmap &= 0x003ff010;
		} else {
			if (rssi_level == 1)
				ratr_bitmap &= 0xfe3f8000;
			else if (rssi_level == 2)
				ratr_bitmap &= 0xfffff000;
			else
				ratr_bitmap &= 0xfffff010;
		}
		break;

	default:
		ratr_index = RATR_INX_WIRELESS_NGB;

		if (rf_type == RF_1T2R)
			ratr_bitmap &= 0x000ff0ff;
		else
			ratr_bitmap &= 0x0f8ff0ff;
		break;
	}

	ratr_index = rtl_mrate_idx_to_arfr_id(hw, ratr_index, wirelessmode);
	sta_entry->ratr_index = ratr_index;
	ratr_bitmap = _rtl8821ae_set_ra_vht_ratr_bitmap(hw, wirelessmode,
							ratr_bitmap);

	RT_TRACE(rtlpriv, COMP_RATR, DBG_LOUD,
		 "ratr_bitmap :%x\n", ratr_bitmap);

	/* *(u32 *)& rate_mask = EF4BYTE((ratr_bitmap & 0x0fffffff) |
				       (ratr_index << 28)); */

	rate_mask[0] = macid;
	rate_mask[1] = ratr_index | (b_shortgi ? 0x80 : 0x00);
	rate_mask[2] = rtlphy->current_chan_bw | ((!update_bw) << 3)
			   | _rtl8821ae_get_vht_eni(wirelessmode, ratr_bitmap)
			   | _rtl8821ae_get_ra_ldpc(hw, macid, sta_entry, wirelessmode);

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
	rtl8821ae_fill_h2c_cmd(hw, H2C_8821AE_RA_MASK, 7, rate_mask);
	_rtl8821ae_set_bcn_ctrl_reg(hw, BIT(3), 0);
}