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
struct TYPE_2__ {scalar_t__ eeprom_bt_coexist; scalar_t__ eeprom_bt_ant_num; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct rtl_hal {int board_type; scalar_t__ oem_id; } ;
struct rtl_efuse {int eeprom_oemid; int txpwr_fromeprom; int board_type; int wowlan_enable; int crystalcap; int antenna_div_cfg; int antenna_div_type; int eeprom_did; int eeprom_svid; int eeprom_smid; int /*<<< orphan*/  autoload_failflag; int /*<<< orphan*/  eeprom_channelplan; int /*<<< orphan*/  channel_plan; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ANT_X1 ; 
 int CGCS_RX_HW_ANTDIV ; 
 int CG_TRX_HW_ANTDIV ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int COUNTRY_CODE_WORLD_WIDE_13 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_CHANNELPLAN ; 
#define  EEPROM_CID_DEFAULT 131 
#define  EEPROM_CID_QMI 130 
#define  EEPROM_CID_TOSHIBA 129 
#define  EEPROM_CID_WHQL 128 
 int EEPROM_CUSTOMER_ID ; 
 int EEPROM_DID ; 
 int EEPROM_MAC_ADDR ; 
 size_t EEPROM_RF_ANTENNA_OPT_88E ; 
 size_t EEPROM_RF_BOARD_OPTION_88E ; 
 size_t EEPROM_RF_FEATURE_OPTION_88E ; 
 int EEPROM_SMID ; 
 int EEPROM_SVID ; 
 int EEPROM_VERSION ; 
 int EEPROM_VID ; 
 size_t EEPROM_XTAL_88E ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE ; 
 int RTL8188E_EEPROM_ID ; 
 scalar_t__ RT_CID_819X_ACER ; 
 scalar_t__ RT_CID_819X_HP ; 
 scalar_t__ RT_CID_819X_LENOVO ; 
 scalar_t__ RT_CID_819X_QMI ; 
 scalar_t__ RT_CID_DEFAULT ; 
 scalar_t__ RT_CID_TOSHIBA ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _rtl88ee_read_txpower_info_from_hwpg (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8188ee_read_bt_coexist_info_from_hwpg (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 scalar_t__ rtl_get_hwinfo (struct ieee80211_hw*,struct rtl_priv*,int /*<<< orphan*/ ,int*,int*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl88ee_read_adapter_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int params[] = {RTL8188E_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13};
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	if (!hwinfo)
		return;

	if (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		goto exit;

	if (rtlefuse->eeprom_oemid == 0xFF)
		rtlefuse->eeprom_oemid = 0;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "EEPROM Customer ID: 0x%2x\n", rtlefuse->eeprom_oemid);
	/* set channel plan from efuse */
	rtlefuse->channel_plan = rtlefuse->eeprom_channelplan;
	/*tx power*/
	_rtl88ee_read_txpower_info_from_hwpg(hw,
					     rtlefuse->autoload_failflag,
					     hwinfo);
	rtlefuse->txpwr_fromeprom = true;

	rtl8188ee_read_bt_coexist_info_from_hwpg(hw,
						 rtlefuse->autoload_failflag,
						 hwinfo);

	/*board type*/
	rtlefuse->board_type =
		((hwinfo[EEPROM_RF_BOARD_OPTION_88E] & 0xE0) >> 5);
	rtlhal->board_type = rtlefuse->board_type;
	/*Wake on wlan*/
	rtlefuse->wowlan_enable =
		((hwinfo[EEPROM_RF_FEATURE_OPTION_88E] & 0x40) >> 6);
	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_88E];
	if (hwinfo[EEPROM_XTAL_88E])
		rtlefuse->crystalcap = 0x20;
	/*antenna diversity*/
	rtlefuse->antenna_div_cfg =
		(hwinfo[EEPROM_RF_BOARD_OPTION_88E] & 0x18) >> 3;
	if (hwinfo[EEPROM_RF_BOARD_OPTION_88E] == 0xFF)
		rtlefuse->antenna_div_cfg = 0;
	if (rtlpriv->btcoexist.eeprom_bt_coexist != 0 &&
	    rtlpriv->btcoexist.eeprom_bt_ant_num == ANT_X1)
		rtlefuse->antenna_div_cfg = 0;

	rtlefuse->antenna_div_type = hwinfo[EEPROM_RF_ANTENNA_OPT_88E];
	if (rtlefuse->antenna_div_type == 0xFF)
		rtlefuse->antenna_div_type = 0x01;
	if (rtlefuse->antenna_div_type == CG_TRX_HW_ANTDIV ||
		rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV)
		rtlefuse->antenna_div_cfg = 1;

	if (rtlhal->oem_id == RT_CID_DEFAULT) {
		switch (rtlefuse->eeprom_oemid) {
		case EEPROM_CID_DEFAULT:
			if (rtlefuse->eeprom_did == 0x8179) {
				if (rtlefuse->eeprom_svid == 0x1025) {
					rtlhal->oem_id = RT_CID_819X_ACER;
				} else if ((rtlefuse->eeprom_svid == 0x10EC &&
				     rtlefuse->eeprom_smid == 0x0179) ||
				     (rtlefuse->eeprom_svid == 0x17AA &&
				     rtlefuse->eeprom_smid == 0x0179)) {
					rtlhal->oem_id = RT_CID_819X_LENOVO;
				} else if (rtlefuse->eeprom_svid == 0x103c &&
					   rtlefuse->eeprom_smid == 0x197d) {
					rtlhal->oem_id = RT_CID_819X_HP;
				} else {
					rtlhal->oem_id = RT_CID_DEFAULT;
				}
			} else {
				rtlhal->oem_id = RT_CID_DEFAULT;
			}
			break;
		case EEPROM_CID_TOSHIBA:
			rtlhal->oem_id = RT_CID_TOSHIBA;
			break;
		case EEPROM_CID_QMI:
			rtlhal->oem_id = RT_CID_819X_QMI;
			break;
		case EEPROM_CID_WHQL:
		default:
			rtlhal->oem_id = RT_CID_DEFAULT;
			break;

		}
	}
exit:
	kfree(hwinfo);
}