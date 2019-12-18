#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int led_opendrain; } ;
struct TYPE_4__ {int btcoexist; scalar_t__ ant_num; } ;
struct TYPE_5__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_3__ ledctl; TYPE_2__ btcoexist; } ;
struct rtl_hal {scalar_t__ hw_type; scalar_t__ external_lna_2g; scalar_t__ external_lna_5g; scalar_t__ external_pa_2g; scalar_t__ external_pa_5g; scalar_t__ oem_id; int /*<<< orphan*/  board_type; } ;
struct rtl_efuse {int eeprom_channelplan; int channel_plan; int crystalcap; int eeprom_thermalmeter; int apk_thermalmeterignore; int* thermalmeter; int antenna_div_cfg; int antenna_div_type; int eeprom_oemid; scalar_t__ autoload_failflag; int /*<<< orphan*/  board_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ANT_X1 ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int COUNTRY_CODE_WORLD_WIDE_13 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_CHANNELPLAN ; 
#define  EEPROM_CID_CCX 132 
#define  EEPROM_CID_QMI 131 
#define  EEPROM_CID_TOSHIBA 130 
#define  EEPROM_CID_WHQL 129 
 int EEPROM_CUSTOMER_ID ; 
 int EEPROM_DID ; 
 int EEPROM_MAC_ADDR ; 
 size_t EEPROM_RF_ANTENNA_OPT_88E ; 
 size_t EEPROM_RF_BOARD_OPTION ; 
 int EEPROM_SMID ; 
 int EEPROM_SVID ; 
 size_t EEPROM_THERMAL_METER ; 
 int EEPROM_VERSION ; 
 int EEPROM_VID ; 
 size_t EEPROM_XTAL_8821AE ; 
 int FIXED_HW_ANTDIV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE ; 
 int /*<<< orphan*/  ODM_BOARD_BT ; 
 int /*<<< orphan*/  ODM_BOARD_DEFAULT ; 
 int /*<<< orphan*/  ODM_BOARD_EXT_LNA ; 
 int /*<<< orphan*/  ODM_BOARD_EXT_LNA_5G ; 
 int /*<<< orphan*/  ODM_BOARD_EXT_PA ; 
 int /*<<< orphan*/  ODM_BOARD_EXT_PA_5G ; 
 int RTL_EEPROM_ID ; 
 scalar_t__ RT_CID_819X_QMI ; 
 scalar_t__ RT_CID_CCX ; 
#define  RT_CID_DEFAULT 128 
 scalar_t__ RT_CID_TOSHIBA ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  _rtl8812ae_read_amplifier_type (struct ieee80211_hw*,int*,scalar_t__) ; 
 int /*<<< orphan*/  _rtl8812ae_read_bt_coexist_info_from_hwpg (struct ieee80211_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  _rtl8821ae_read_bt_coexist_info_from_hwpg (struct ieee80211_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  _rtl8821ae_read_pa_type (struct ieee80211_hw*,int*,scalar_t__) ; 
 int /*<<< orphan*/  _rtl8821ae_read_rfe_type (struct ieee80211_hw*,int*,scalar_t__) ; 
 int /*<<< orphan*/  _rtl8821ae_read_txpower_info_from_hwpg (struct ieee80211_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 scalar_t__ rtl_get_hwinfo (struct ieee80211_hw*,struct rtl_priv*,int /*<<< orphan*/ ,int*,int*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8821ae_read_adapter_info(struct ieee80211_hw *hw, bool b_pseudo_test)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int params[] = {RTL_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13};
	u8 *hwinfo;

	if (b_pseudo_test) {
		;/* need add */
	}

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	if (!hwinfo)
		return;

	if (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		goto exit;

	_rtl8821ae_read_txpower_info_from_hwpg(hw, rtlefuse->autoload_failflag,
					       hwinfo);

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
		_rtl8812ae_read_amplifier_type(hw, hwinfo,
					       rtlefuse->autoload_failflag);
		_rtl8812ae_read_bt_coexist_info_from_hwpg(hw,
				rtlefuse->autoload_failflag, hwinfo);
	} else {
		_rtl8821ae_read_pa_type(hw, hwinfo, rtlefuse->autoload_failflag);
		_rtl8821ae_read_bt_coexist_info_from_hwpg(hw,
				rtlefuse->autoload_failflag, hwinfo);
	}

	_rtl8821ae_read_rfe_type(hw, hwinfo, rtlefuse->autoload_failflag);
	/*board type*/
	rtlefuse->board_type = ODM_BOARD_DEFAULT;
	if (rtlhal->external_lna_2g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_LNA;
	if (rtlhal->external_lna_5g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_LNA_5G;
	if (rtlhal->external_pa_2g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_PA;
	if (rtlhal->external_pa_5g != 0)
		rtlefuse->board_type |= ODM_BOARD_EXT_PA_5G;

	if (rtlpriv->btcoexist.btc_info.btcoexist == 1)
		rtlefuse->board_type |= ODM_BOARD_BT;

	rtlhal->board_type = rtlefuse->board_type;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "board_type = 0x%x\n", rtlefuse->board_type);

	rtlefuse->eeprom_channelplan = *(u8 *)&hwinfo[EEPROM_CHANNELPLAN];
	if (rtlefuse->eeprom_channelplan == 0xff)
		rtlefuse->eeprom_channelplan = 0x7F;

	/* set channel plan from efuse */
	rtlefuse->channel_plan = rtlefuse->eeprom_channelplan;

	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_8821AE];
	if (rtlefuse->crystalcap == 0xFF)
		rtlefuse->crystalcap = 0x20;

	rtlefuse->eeprom_thermalmeter = *(u8 *)&hwinfo[EEPROM_THERMAL_METER];
	if ((rtlefuse->eeprom_thermalmeter == 0xff) ||
	    rtlefuse->autoload_failflag) {
		rtlefuse->apk_thermalmeterignore = true;
		rtlefuse->eeprom_thermalmeter = 0xff;
	}

	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);

	if (!rtlefuse->autoload_failflag) {
		rtlefuse->antenna_div_cfg =
		  (hwinfo[EEPROM_RF_BOARD_OPTION] & 0x18) >> 3;
		if (hwinfo[EEPROM_RF_BOARD_OPTION] == 0xff)
			rtlefuse->antenna_div_cfg = 0;

		if (rtlpriv->btcoexist.btc_info.btcoexist == 1 &&
		    rtlpriv->btcoexist.btc_info.ant_num == ANT_X1)
			rtlefuse->antenna_div_cfg = 0;

		rtlefuse->antenna_div_type = hwinfo[EEPROM_RF_ANTENNA_OPT_88E];
		if (rtlefuse->antenna_div_type == 0xff)
			rtlefuse->antenna_div_type = FIXED_HW_ANTDIV;
	} else {
		rtlefuse->antenna_div_cfg = 0;
		rtlefuse->antenna_div_type = 0;
	}

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		"SWAS: bHwAntDiv = %x, TRxAntDivType = %x\n",
		rtlefuse->antenna_div_cfg, rtlefuse->antenna_div_type);

	rtlpriv->ledctl.led_opendrain = true;

	if (rtlhal->oem_id == RT_CID_DEFAULT) {
		switch (rtlefuse->eeprom_oemid) {
		case RT_CID_DEFAULT:
			break;
		case EEPROM_CID_TOSHIBA:
			rtlhal->oem_id = RT_CID_TOSHIBA;
			break;
		case EEPROM_CID_CCX:
			rtlhal->oem_id = RT_CID_CCX;
			break;
		case EEPROM_CID_QMI:
			rtlhal->oem_id = RT_CID_819X_QMI;
			break;
		case EEPROM_CID_WHQL:
			break;
		default:
			break;
		}
	}
exit:
	kfree(hwinfo);
}