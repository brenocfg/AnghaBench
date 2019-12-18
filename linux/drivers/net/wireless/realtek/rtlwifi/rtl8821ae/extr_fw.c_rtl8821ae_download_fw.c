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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct rtlwifi_firmware_header {int /*<<< orphan*/  signature; int /*<<< orphan*/  version; int /*<<< orphan*/  subversion; } ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_hal {int version; scalar_t__ mac_func_enable; scalar_t__ fwsize; scalar_t__ pfirmware; int /*<<< orphan*/  fw_subversion; void* fw_version; scalar_t__ wowlan_fwsize; scalar_t__ wowlan_firmware; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8821ae { ____Placeholder_version_8821ae } version_8821ae ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  HAL_DEF_WOWLAN ; 
 scalar_t__ IS_FW_HEADER_EXIST_8812 (struct rtlwifi_firmware_header*) ; 
 scalar_t__ IS_FW_HEADER_EXIST_8821 (struct rtlwifi_firmware_header*) ; 
 int /*<<< orphan*/  REG_MCUFWDL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _rtl8821ae_enable_fw_download (struct ieee80211_hw*,int) ; 
 int _rtl8821ae_fw_free_to_go (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl8821ae_wait_for_h2c_cmd_finish (struct rtl_priv*) ; 
 int /*<<< orphan*/  _rtl8821ae_write_fw (struct ieee80211_hw*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8821ae_firmware_selfreset (struct ieee80211_hw*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rtl8821ae_download_fw(struct ieee80211_hw *hw, bool buse_wake_on_wlan_fw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtlwifi_firmware_header *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	int err;
	bool support_remote_wakeup;
	enum version_8821ae version = rtlhal->version;

	rtlpriv->cfg->ops->get_hw_reg(hw, HAL_DEF_WOWLAN,
				      (u8 *)(&support_remote_wakeup));

	if (support_remote_wakeup)
		_rtl8821ae_wait_for_h2c_cmd_finish(rtlpriv);

	if (buse_wake_on_wlan_fw) {
		if (!rtlhal->wowlan_firmware)
			return 1;

		pfwheader =
		  (struct rtlwifi_firmware_header *)rtlhal->wowlan_firmware;
		rtlhal->fw_version = le16_to_cpu(pfwheader->version);
		rtlhal->fw_subversion = pfwheader->subversion;
		pfwdata = (u8 *)rtlhal->wowlan_firmware;
		fwsize = rtlhal->wowlan_fwsize;
	} else {
		if (!rtlhal->pfirmware)
			return 1;

		pfwheader =
		  (struct rtlwifi_firmware_header *)rtlhal->pfirmware;
		rtlhal->fw_version = le16_to_cpu(pfwheader->version);
		rtlhal->fw_subversion = pfwheader->subversion;
		pfwdata = (u8 *)rtlhal->pfirmware;
		fwsize = rtlhal->fwsize;
	}

	RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
		 "%s Firmware SIZE %d\n",
		 buse_wake_on_wlan_fw ? "Wowlan" : "Normal", fwsize);

	if (IS_FW_HEADER_EXIST_8812(pfwheader) ||
	    IS_FW_HEADER_EXIST_8821(pfwheader)) {
		RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
			 "Firmware Version(%d), Signature(%#x)\n",
			 pfwheader->version, pfwheader->signature);

		pfwdata = pfwdata + sizeof(struct rtlwifi_firmware_header);
		fwsize = fwsize - sizeof(struct rtlwifi_firmware_header);
	}

	if (rtlhal->mac_func_enable) {
		if (rtl_read_byte(rtlpriv, REG_MCUFWDL) & BIT(7)) {
			rtl_write_byte(rtlpriv, REG_MCUFWDL, 0x00);
			rtl8821ae_firmware_selfreset(hw);
		}
	}
	_rtl8821ae_enable_fw_download(hw, true);
	_rtl8821ae_write_fw(hw, version, pfwdata, fwsize);
	_rtl8821ae_enable_fw_download(hw, false);

	err = _rtl8821ae_fw_free_to_go(hw);
	if (err) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_DMESG,
			 "Firmware is not ready to run!\n");
	} else {
		RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD,
			 "Firmware is ready to run!\n");
	}

	return 0;
}