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
struct TYPE_14__ {int /*<<< orphan*/ * pfirmware; int /*<<< orphan*/  macphymode; void* bandset; void* current_bandtype; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int reg_fwctrl_lps; int reg_max_lps_awakeintvl; int /*<<< orphan*/  fwctrl_psmode; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;
struct TYPE_9__ {int dm_initialgain_enable; scalar_t__ thermalvalue; scalar_t__ disable_framebursting; scalar_t__ dm_flag; } ;
struct TYPE_8__ {int /*<<< orphan*/  btc_ops; } ;
struct rtl_priv {int max_fw_size; TYPE_7__ rtlhal; TYPE_6__ io; TYPE_5__ psc; TYPE_4__* cfg; TYPE_2__ dm; TYPE_1__ btcoexist; } ;
struct rtl_pci {int transmit_config; int receive_config; int /*<<< orphan*/  msi_support; void** irq_mask; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_11__ {TYPE_3__* mod_params; } ;
struct TYPE_10__ {scalar_t__ disable_watchdog; int /*<<< orphan*/  msi_support; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;

/* Variables and functions */
 void* BAND_ON_2_4G ; 
 int BIT (int) ; 
 int CFENDFORM ; 
 int /*<<< orphan*/  FW_PS_DTIM_MODE ; 
 int /*<<< orphan*/  FW_PS_MAX_MODE ; 
 int /*<<< orphan*/  FW_PS_MIN_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_81XXC_VENDOR_UMC_B_CUT (int /*<<< orphan*/ ) ; 
 int PHIMR_BEDOK ; 
 int PHIMR_BKDOK ; 
 int PHIMR_C2HCMD ; 
 int PHIMR_HIGHDOK ; 
 int PHIMR_HISRE_IND ; 
 int PHIMR_MGNTDOK ; 
 int PHIMR_PSTIMEOUT ; 
 int PHIMR_RDU ; 
 int PHIMR_ROK ; 
 int PHIMR_RXFOVW ; 
 int PHIMR_TSF_BIT32_TOGGLE ; 
 int PHIMR_TXBCNOK ; 
 int PHIMR_VIDOK ; 
 int PHIMR_VODOK ; 
 int RCR_AB ; 
 int RCR_ACF ; 
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
 int /*<<< orphan*/  SINGLEMAC_SINGLEPHY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8723e_bt_reg_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8723e_init_aspm_vars (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_btc_get_ops_pointer () ; 
 int /*<<< orphan*/  rtl_fw_cb ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

int rtl8723e_init_sw_vars(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int err = 0;
	char *fw_name = "rtlwifi/rtl8723fw.bin";

	rtl8723e_bt_reg_init(hw);

	rtlpriv->btcoexist.btc_ops = rtl_btc_get_ops_pointer();

	rtlpriv->dm.dm_initialgain_enable = 1;
	rtlpriv->dm.dm_flag = 0;
	rtlpriv->dm.disable_framebursting = 0;
	rtlpriv->dm.thermalvalue = 0;
	rtlpci->transmit_config = CFENDFORM | BIT(12) | BIT(13);

	/* compatible 5G band 88ce just 2.4G band & smsp */
	rtlpriv->rtlhal.current_bandtype = BAND_ON_2_4G;
	rtlpriv->rtlhal.bandset = BAND_ON_2_4G;
	rtlpriv->rtlhal.macphymode = SINGLEMAC_SINGLEPHY;

	rtlpci->receive_config = (RCR_APPFCS |
				  RCR_APP_MIC |
				  RCR_APP_ICV |
				  RCR_APP_PHYST_RXFF |
				  RCR_HTC_LOC_CTRL |
				  RCR_AMF |
				  RCR_ACF |
				  RCR_ADF |
				  RCR_AICV |
				  RCR_AB |
				  RCR_AM |
				  RCR_APM |
				  0);

	rtlpci->irq_mask[0] =
	    (u32) (PHIMR_ROK |
		   PHIMR_RDU |
		   PHIMR_VODOK |
		   PHIMR_VIDOK |
		   PHIMR_BEDOK |
		   PHIMR_BKDOK |
		   PHIMR_MGNTDOK |
		   PHIMR_HIGHDOK |
		   PHIMR_C2HCMD |
		   PHIMR_HISRE_IND |
		   PHIMR_TSF_BIT32_TOGGLE |
		   PHIMR_TXBCNOK |
		   PHIMR_PSTIMEOUT |
		   0);

	rtlpci->irq_mask[1]	=
		 (u32)(PHIMR_RXFOVW |
				0);

	/* for LPS & IPS */
	rtlpriv->psc.inactiveps = rtlpriv->cfg->mod_params->inactiveps;
	rtlpriv->psc.swctrl_lps = rtlpriv->cfg->mod_params->swctrl_lps;
	rtlpriv->psc.fwctrl_lps = rtlpriv->cfg->mod_params->fwctrl_lps;
	rtlpci->msi_support = rtlpriv->cfg->mod_params->msi_support;
	if (rtlpriv->cfg->mod_params->disable_watchdog)
		pr_info("watchdog disabled\n");
	rtlpriv->psc.reg_fwctrl_lps = 3;
	rtlpriv->psc.reg_max_lps_awakeintvl = 5;
	rtl8723e_init_aspm_vars(hw);

	if (rtlpriv->psc.reg_fwctrl_lps == 1)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MIN_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 2)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MAX_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 3)
		rtlpriv->psc.fwctrl_psmode = FW_PS_DTIM_MODE;

	/* for firmware buf */
	rtlpriv->rtlhal.pfirmware = vzalloc(0x6000);
	if (!rtlpriv->rtlhal.pfirmware) {
		pr_err("Can't alloc buffer for fw.\n");
		return 1;
	}

	if (IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version))
		fw_name = "rtlwifi/rtl8723fw_B.bin";

	rtlpriv->max_fw_size = 0x6000;
	pr_info("Using firmware %s\n", fw_name);
	err = request_firmware_nowait(THIS_MODULE, 1, fw_name,
				      rtlpriv->io.dev, GFP_KERNEL, hw,
				      rtl_fw_cb);
	if (err) {
		pr_err("Failed to request firmware!\n");
		vfree(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = NULL;
		return 1;
	}
	return 0;
}