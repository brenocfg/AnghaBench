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
typedef  scalar_t__ u32 ;
struct rtlwifi_firmware_header {int /*<<< orphan*/  subversion; int /*<<< orphan*/  version; int /*<<< orphan*/  signature; } ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int version; int /*<<< orphan*/  fw_subversion; int /*<<< orphan*/  fw_version; scalar_t__ fwsize; scalar_t__ pfirmware; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8192c { ____Placeholder_version_8192c } version_8192c ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ IS_FW_HEADER_EXIST (struct rtlwifi_firmware_header*) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _rtl92c_enable_fw_download (struct ieee80211_hw*,int) ; 
 int _rtl92c_fw_free_to_go (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl92c_write_fw (struct ieee80211_hw*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

int rtl92c_download_fw(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtlwifi_firmware_header *pfwheader;
	u8 *pfwdata;
	u32 fwsize;
	int err;
	enum version_8192c version = rtlhal->version;

	if (!rtlhal->pfirmware)
		return 1;

	pfwheader = (struct rtlwifi_firmware_header *)rtlhal->pfirmware;
	pfwdata = (u8 *)rtlhal->pfirmware;
	fwsize = rtlhal->fwsize;
	if (IS_FW_HEADER_EXIST(pfwheader)) {
		RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
			 "Firmware Version(%d), Signature(%#x),Size(%d)\n",
			  pfwheader->version, pfwheader->signature,
			  (int)sizeof(struct rtlwifi_firmware_header));

		rtlhal->fw_version = le16_to_cpu(pfwheader->version);
		rtlhal->fw_subversion = pfwheader->subversion;
		pfwdata = pfwdata + sizeof(struct rtlwifi_firmware_header);
		fwsize = fwsize - sizeof(struct rtlwifi_firmware_header);
	}

	_rtl92c_enable_fw_download(hw, true);
	_rtl92c_write_fw(hw, version, pfwdata, fwsize);
	_rtl92c_enable_fw_download(hw, false);

	err = _rtl92c_fw_free_to_go(hw);
	if (err)
		pr_err("Firmware is not ready to run!\n");

	return 0;
}