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
typedef  int u16 ;
struct TYPE_3__ {int btcoexist; } ;
struct TYPE_4__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_2__ btcoexist; } ;
struct rtl_hal {scalar_t__ oem_id; int /*<<< orphan*/  package_type; int /*<<< orphan*/  board_type; } ;
struct rtl_efuse {int crystalcap; int eeprom_smid; int eeprom_oemid; int eeprom_did; int eeprom_svid; int /*<<< orphan*/  eeprom_channelplan; int /*<<< orphan*/  channel_plan; int /*<<< orphan*/  board_type; int /*<<< orphan*/  autoload_failflag; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int COUNTRY_CODE_WORLD_WIDE_13 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_CHANNELPLAN ; 
#define  EEPROM_CID_CCX 132 
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
 size_t EEPROM_XTAL_8723BE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWSET_MAX_SIZE ; 
 int RTL8723BE_EEPROM_ID ; 
 void* RT_CID_819X_ACER ; 
 scalar_t__ RT_CID_819X_CLEVO ; 
 scalar_t__ RT_CID_819X_DELL ; 
 void* RT_CID_819X_EDIMAX_ASUS ; 
 scalar_t__ RT_CID_819X_HP ; 
 scalar_t__ RT_CID_819X_LENOVO ; 
 void* RT_CID_819X_PRONETS ; 
 void* RT_CID_819X_QMI ; 
 scalar_t__ RT_CID_819X_SAMSUNG ; 
 scalar_t__ RT_CID_CCX ; 
 scalar_t__ RT_CID_DEFAULT ; 
 void* RT_CID_TOSHIBA ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl8723be_read_package_type (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8723be_read_txpower_info_from_hwpg (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723be_read_bt_coexist_info_from_hwpg (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 scalar_t__ rtl_get_hwinfo (struct ieee80211_hw*,struct rtl_priv*,int /*<<< orphan*/ ,int*,int*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8723be_read_adapter_info(struct ieee80211_hw *hw,
					 bool pseudo_test)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int params[] = {RTL8723BE_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			COUNTRY_CODE_WORLD_WIDE_13};
	u8 *hwinfo;
	int i;
	bool is_toshiba_smid1 = false;
	bool is_toshiba_smid2 = false;
	bool is_samsung_smid = false;
	bool is_lenovo_smid = false;
	u16 toshiba_smid1[] = {
		0x6151, 0x6152, 0x6154, 0x6155, 0x6177, 0x6178, 0x6179, 0x6180,
		0x7151, 0x7152, 0x7154, 0x7155, 0x7177, 0x7178, 0x7179, 0x7180,
		0x8151, 0x8152, 0x8154, 0x8155, 0x8181, 0x8182, 0x8184, 0x8185,
		0x9151, 0x9152, 0x9154, 0x9155, 0x9181, 0x9182, 0x9184, 0x9185
	};
	u16 toshiba_smid2[] = {
		0x6181, 0x6184, 0x6185, 0x7181, 0x7182, 0x7184, 0x7185, 0x8181,
		0x8182, 0x8184, 0x8185, 0x9181, 0x9182, 0x9184, 0x9185
	};
	u16 samsung_smid[] = {
		0x6191, 0x6192, 0x6193, 0x7191, 0x7192, 0x7193, 0x8191, 0x8192,
		0x8193, 0x9191, 0x9192, 0x9193
	};
	u16 lenovo_smid[] = {
		0x8195, 0x9195, 0x7194, 0x8200, 0x8201, 0x8202, 0x9199, 0x9200
	};

	if (pseudo_test) {
		/* needs to be added */
		return;
	}

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	if (!hwinfo)
		return;

	if (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		goto exit;

	/*parse xtal*/
	rtlefuse->crystalcap = hwinfo[EEPROM_XTAL_8723BE];
	if (rtlefuse->crystalcap == 0xFF)
		rtlefuse->crystalcap = 0x20;

	_rtl8723be_read_txpower_info_from_hwpg(hw, rtlefuse->autoload_failflag,
					       hwinfo);

	rtl8723be_read_bt_coexist_info_from_hwpg(hw,
						 rtlefuse->autoload_failflag,
						 hwinfo);

	if (rtlpriv->btcoexist.btc_info.btcoexist == 1)
		rtlefuse->board_type |= BIT(2); /* ODM_BOARD_BT */

	rtlhal->board_type = rtlefuse->board_type;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "board_type = 0x%x\n", rtlefuse->board_type);

	rtlhal->package_type = _rtl8723be_read_package_type(hw);

	/* set channel plan from efuse */
	rtlefuse->channel_plan = rtlefuse->eeprom_channelplan;

	if (rtlhal->oem_id == RT_CID_DEFAULT) {
		/* Does this one have a Toshiba SMID from group 1? */
		for (i = 0; i < ARRAY_SIZE(toshiba_smid1); i++) {
			if (rtlefuse->eeprom_smid == toshiba_smid1[i]) {
				is_toshiba_smid1 = true;
				break;
			}
		}
		/* Does this one have a Toshiba SMID from group 2? */
		for (i = 0; i < ARRAY_SIZE(toshiba_smid2); i++) {
			if (rtlefuse->eeprom_smid == toshiba_smid2[i]) {
				is_toshiba_smid2 = true;
				break;
			}
		}
		/* Does this one have a Samsung SMID? */
		for (i = 0; i < ARRAY_SIZE(samsung_smid); i++) {
			if (rtlefuse->eeprom_smid == samsung_smid[i]) {
				is_samsung_smid = true;
				break;
			}
		}
		/* Does this one have a Lenovo SMID? */
		for (i = 0; i < ARRAY_SIZE(lenovo_smid); i++) {
			if (rtlefuse->eeprom_smid == lenovo_smid[i]) {
				is_lenovo_smid = true;
				break;
			}
		}
		switch (rtlefuse->eeprom_oemid) {
		case EEPROM_CID_DEFAULT:
			if (rtlefuse->eeprom_did == 0x8176) {
				if (rtlefuse->eeprom_svid == 0x10EC &&
				    is_toshiba_smid1) {
					rtlhal->oem_id = RT_CID_TOSHIBA;
				} else if (rtlefuse->eeprom_svid == 0x1025) {
					rtlhal->oem_id = RT_CID_819X_ACER;
				} else if (rtlefuse->eeprom_svid == 0x10EC &&
					   is_samsung_smid) {
					rtlhal->oem_id = RT_CID_819X_SAMSUNG;
				} else if (rtlefuse->eeprom_svid == 0x10EC &&
					   is_lenovo_smid) {
					rtlhal->oem_id = RT_CID_819X_LENOVO;
				} else if ((rtlefuse->eeprom_svid == 0x10EC &&
					    rtlefuse->eeprom_smid == 0x8197) ||
					   (rtlefuse->eeprom_svid == 0x10EC &&
					    rtlefuse->eeprom_smid == 0x9196)) {
					rtlhal->oem_id = RT_CID_819X_CLEVO;
				} else if ((rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x8194) ||
					   (rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x8198) ||
					   (rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x9197) ||
					   (rtlefuse->eeprom_svid == 0x1028 &&
					    rtlefuse->eeprom_smid == 0x9198)) {
					rtlhal->oem_id = RT_CID_819X_DELL;
				} else if ((rtlefuse->eeprom_svid == 0x103C &&
					    rtlefuse->eeprom_smid == 0x1629)) {
					rtlhal->oem_id = RT_CID_819X_HP;
				} else if ((rtlefuse->eeprom_svid == 0x1A32 &&
					   rtlefuse->eeprom_smid == 0x2315)) {
					rtlhal->oem_id = RT_CID_819X_QMI;
				} else if ((rtlefuse->eeprom_svid == 0x10EC &&
					   rtlefuse->eeprom_smid == 0x8203)) {
					rtlhal->oem_id = RT_CID_819X_PRONETS;
				} else if ((rtlefuse->eeprom_svid == 0x1043 &&
					   rtlefuse->eeprom_smid == 0x84B5)) {
					rtlhal->oem_id = RT_CID_819X_EDIMAX_ASUS;
				} else {
					rtlhal->oem_id = RT_CID_DEFAULT;
				}
			} else if (rtlefuse->eeprom_did == 0x8178) {
				if (rtlefuse->eeprom_svid == 0x10EC &&
				    is_toshiba_smid2)
					rtlhal->oem_id = RT_CID_TOSHIBA;
				else if (rtlefuse->eeprom_svid == 0x1025)
					rtlhal->oem_id = RT_CID_819X_ACER;
				else if ((rtlefuse->eeprom_svid == 0x10EC &&
					  rtlefuse->eeprom_smid == 0x8186))
					rtlhal->oem_id = RT_CID_819X_PRONETS;
				else if ((rtlefuse->eeprom_svid == 0x1043 &&
					  rtlefuse->eeprom_smid == 0x84B6))
					rtlhal->oem_id =
							RT_CID_819X_EDIMAX_ASUS;
				else
					rtlhal->oem_id = RT_CID_DEFAULT;
			} else {
					rtlhal->oem_id = RT_CID_DEFAULT;
			}
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
			rtlhal->oem_id = RT_CID_DEFAULT;
			break;
		}
	}
exit:
	kfree(hwinfo);
}