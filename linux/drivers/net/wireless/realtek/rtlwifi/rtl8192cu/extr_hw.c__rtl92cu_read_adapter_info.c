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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {scalar_t__ oem_id; } ;
struct rtl_efuse {int txpwr_fromeprom; int eeprom_oemid; int eeprom_did; int eeprom_svid; int eeprom_smid; int /*<<< orphan*/  autoload_failflag; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int EEPROM_CHANNELPLAN ; 
#define  EEPROM_CID_DEFAULT 131 
#define  EEPROM_CID_QMI 130 
#define  EEPROM_CID_TOSHIBA 129 
#define  EEPROM_CID_WHQL 128 
 int EEPROM_CUSTOMER_ID ; 
 int EEPROM_DID ; 
 int EEPROM_MAC_ADDR ; 
 int EEPROM_SMID ; 
 int EEPROM_SVID ; 
 int EEPROM_VERSION ; 
 int EEPROM_VID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE ; 
 int RTL8190_EEPROM_ID ; 
 scalar_t__ RT_CID_819X_HP ; 
 scalar_t__ RT_CID_819X_QMI ; 
 scalar_t__ RT_CID_DEFAULT ; 
 scalar_t__ RT_CID_TOSHIBA ; 
 int /*<<< orphan*/  _rtl92cu_read_board_type (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92cu_read_txpower_info_from_hwpg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 scalar_t__ rtl_get_hwinfo (struct ieee80211_hw*,struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92cu_read_adapter_info(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int params[] = {RTL8190_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			0};
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	if (!hwinfo)
		return;

	if (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		goto exit;

	_rtl92cu_read_txpower_info_from_hwpg(hw,
					   rtlefuse->autoload_failflag, hwinfo);
	_rtl92cu_read_board_type(hw, hwinfo);

	rtlefuse->txpwr_fromeprom = true;
	if (rtlhal->oem_id == RT_CID_DEFAULT) {
		switch (rtlefuse->eeprom_oemid) {
		case EEPROM_CID_DEFAULT:
			if (rtlefuse->eeprom_did == 0x8176) {
				if ((rtlefuse->eeprom_svid == 0x103C &&
				     rtlefuse->eeprom_smid == 0x1629))
					rtlhal->oem_id = RT_CID_819X_HP;
				else
					rtlhal->oem_id = RT_CID_DEFAULT;
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