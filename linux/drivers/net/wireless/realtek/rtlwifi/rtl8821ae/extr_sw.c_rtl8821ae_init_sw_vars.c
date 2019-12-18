#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_11__ {int /*<<< orphan*/ * pfirmware; int /*<<< orphan*/ * wowlan_firmware; int /*<<< orphan*/  macphymode; int /*<<< orphan*/  bandset; int /*<<< orphan*/  current_bandtype; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {int wo_wlan_mode; int reg_fwctrl_lps; int reg_max_lps_awakeintvl; int /*<<< orphan*/  fwctrl_psmode; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;
struct TYPE_10__ {int dm_initialgain_enable; scalar_t__ thermalvalue; scalar_t__ disable_framebursting; scalar_t__ dm_flag; } ;
struct TYPE_9__ {int /*<<< orphan*/  btc_ops; } ;
struct rtl_priv {int max_fw_size; TYPE_4__ rtlhal; TYPE_1__ io; TYPE_7__ psc; TYPE_6__* cfg; TYPE_3__ dm; TYPE_2__ btcoexist; } ;
struct rtl_pci {int transmit_config; int receive_config; int /*<<< orphan*/  int_clear; int /*<<< orphan*/  msi_support; void* sys_irq_mask; void** irq_mask; } ;
struct rtl_mac {int ht_enable; scalar_t__ vht_stbc_cap; scalar_t__ vht_cur_stbc; scalar_t__ vht_ldpc_cap; scalar_t__ vht_cur_ldpc; scalar_t__ ht_stbc_cap; scalar_t__ ht_cur_stbc; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_13__ {TYPE_5__* mod_params; } ;
struct TYPE_12__ {scalar_t__ disable_watchdog; int /*<<< orphan*/  int_clear; int /*<<< orphan*/  msi_support; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  BAND_ON_BOTH ; 
 int BIT (int) ; 
 int CFENDFORM ; 
 int /*<<< orphan*/  FW_PS_DTIM_MODE ; 
 int /*<<< orphan*/  FW_PS_MAX_MODE ; 
 int /*<<< orphan*/  FW_PS_MIN_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int HSIMR_PDN_INT_EN ; 
 int HSIMR_RON_INT_EN ; 
 int IMR_BEDOK ; 
 int IMR_BKDOK ; 
 int IMR_C2HCMD ; 
 int IMR_GTINT3 ; 
 int IMR_HIGHDOK ; 
 int IMR_HSISR_IND_ON_INT ; 
 int IMR_MGNTDOK ; 
 int IMR_PSTIMEOUT ; 
 int IMR_RDU ; 
 int IMR_ROK ; 
 int IMR_RXFOVW ; 
 int IMR_TXFOVW ; 
 int IMR_VIDOK ; 
 int IMR_VODOK ; 
 int RCR_AB ; 
 int RCR_ACF ; 
 int RCR_ACRC32 ; 
 int RCR_ADF ; 
 int RCR_AICV ; 
 int RCR_AM ; 
 int RCR_AMF ; 
 int RCR_APM ; 
 int RCR_APPFCS ; 
 int RCR_APP_ICV ; 
 int RCR_APP_MIC ; 
 int RCR_APP_PHYST_RXFF ; 
 int RCR_HTC_LOC_CTRL ; 
 int RCR_NONQOS_VHT ; 
 int /*<<< orphan*/  SINGLEMAC_SINGLEPHY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int WAKE_ON_MAGIC_PACKET ; 
 int WAKE_ON_PATTERN_MATCH ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8821ae_bt_reg_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8821ae_init_aspm_vars (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_btc_get_ops_pointer () ; 
 int /*<<< orphan*/  rtl_fw_cb ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_wowlan_fw_cb ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 void* vzalloc (int) ; 

int rtl8821ae_init_sw_vars(struct ieee80211_hw *hw)
{
	int err = 0;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	char *fw_name, *wowlan_fw_name;

	rtl8821ae_bt_reg_init(hw);
	rtlpriv->btcoexist.btc_ops = rtl_btc_get_ops_pointer();

	rtlpriv->dm.dm_initialgain_enable = 1;
	rtlpriv->dm.dm_flag = 0;
	rtlpriv->dm.disable_framebursting = 0;
	rtlpriv->dm.thermalvalue = 0;
	rtlpci->transmit_config = CFENDFORM | BIT(15) | BIT(24) | BIT(25);

	mac->ht_enable = true;
	mac->ht_cur_stbc = 0;
	mac->ht_stbc_cap = 0;
	mac->vht_cur_ldpc = 0;
	mac->vht_ldpc_cap = 0;
	mac->vht_cur_stbc = 0;
	mac->vht_stbc_cap = 0;

	rtlpriv->rtlhal.current_bandtype = BAND_ON_2_4G;
	/*following 2 is for register 5G band, refer to _rtl_init_mac80211()*/
	rtlpriv->rtlhal.bandset = BAND_ON_BOTH;
	rtlpriv->rtlhal.macphymode = SINGLEMAC_SINGLEPHY;

	rtlpci->receive_config = (RCR_APPFCS	|
				RCR_APP_MIC		|
				RCR_APP_ICV		|
				RCR_APP_PHYST_RXFF	|
				RCR_NONQOS_VHT		|
				RCR_HTC_LOC_CTRL	|
				RCR_AMF			|
				RCR_ACF			|
			/*This bit controls the PS-Poll packet filter.*/
				RCR_ADF			|
				RCR_AICV		|
				RCR_ACRC32		|
				RCR_AB			|
				RCR_AM			|
				RCR_APM			|
				0);

	rtlpci->irq_mask[0] =
	     (u32)(IMR_PSTIMEOUT			|
				IMR_GTINT3		|
				IMR_HSISR_IND_ON_INT	|
				IMR_C2HCMD		|
				IMR_HIGHDOK		|
				IMR_MGNTDOK		|
				IMR_BKDOK		|
				IMR_BEDOK		|
				IMR_VIDOK		|
				IMR_VODOK		|
				IMR_RDU			|
				IMR_ROK			|
				0);

	rtlpci->irq_mask[1]	=
		 (u32)(IMR_RXFOVW |
				IMR_TXFOVW |
				0);
	rtlpci->sys_irq_mask = (u32)(HSIMR_PDN_INT_EN	|
				      HSIMR_RON_INT_EN	|
				      0);
	/* for WOWLAN */
	rtlpriv->psc.wo_wlan_mode = WAKE_ON_MAGIC_PACKET |
				    WAKE_ON_PATTERN_MATCH;

	/* for LPS & IPS */
	rtlpriv->psc.inactiveps = rtlpriv->cfg->mod_params->inactiveps;
	rtlpriv->psc.swctrl_lps = rtlpriv->cfg->mod_params->swctrl_lps;
	rtlpriv->psc.fwctrl_lps = rtlpriv->cfg->mod_params->fwctrl_lps;
	rtlpci->msi_support = rtlpriv->cfg->mod_params->msi_support;
	rtlpci->int_clear = rtlpriv->cfg->mod_params->int_clear;
	if (rtlpriv->cfg->mod_params->disable_watchdog)
		pr_info("watchdog disabled\n");
	rtlpriv->psc.reg_fwctrl_lps = 2;
	rtlpriv->psc.reg_max_lps_awakeintvl = 2;

	/* for ASPM, you can close aspm through
	 * set const_support_pciaspm = 0
	 */
	rtl8821ae_init_aspm_vars(hw);

	if (rtlpriv->psc.reg_fwctrl_lps == 1)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MIN_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 2)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MAX_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 3)
		rtlpriv->psc.fwctrl_psmode = FW_PS_DTIM_MODE;

	/* for firmware buf */
	rtlpriv->rtlhal.pfirmware = vzalloc(0x8000);
	if (!rtlpriv->rtlhal.pfirmware) {
		pr_err("Can't alloc buffer for fw.\n");
		return 1;
	}
	rtlpriv->rtlhal.wowlan_firmware = vzalloc(0x8000);
	if (!rtlpriv->rtlhal.wowlan_firmware) {
		pr_err("Can't alloc buffer for wowlan fw.\n");
		vfree(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = NULL;
		return 1;
	}

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
		fw_name = "rtlwifi/rtl8812aefw.bin";
		wowlan_fw_name = "rtlwifi/rtl8812aefw_wowlan.bin";
	} else {
		fw_name = "rtlwifi/rtl8821aefw_29.bin";
		wowlan_fw_name = "rtlwifi/rtl8821aefw_wowlan.bin";
	}

	rtlpriv->max_fw_size = 0x8000;
	/*load normal firmware*/
	pr_info("Using firmware %s\n", fw_name);
	err = request_firmware_nowait(THIS_MODULE, 1, fw_name,
				      rtlpriv->io.dev, GFP_KERNEL, hw,
				      rtl_fw_cb);
	if (err) {
		pr_err("Failed to request normal firmware!\n");
		vfree(rtlpriv->rtlhal.wowlan_firmware);
		vfree(rtlpriv->rtlhal.pfirmware);
		return 1;
	}
	/*load wowlan firmware*/
	pr_info("Using firmware %s\n", wowlan_fw_name);
	err = request_firmware_nowait(THIS_MODULE, 1,
				      wowlan_fw_name,
				      rtlpriv->io.dev, GFP_KERNEL, hw,
				      rtl_wowlan_fw_cb);
	if (err) {
		pr_err("Failed to request wowlan firmware!\n");
		vfree(rtlpriv->rtlhal.wowlan_firmware);
		vfree(rtlpriv->rtlhal.pfirmware);
		return 1;
	}
	return 0;
}