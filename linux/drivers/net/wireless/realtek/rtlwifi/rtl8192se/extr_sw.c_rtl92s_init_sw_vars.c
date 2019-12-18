#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int u16 ;
struct TYPE_12__ {int /*<<< orphan*/ * pfirmware; int /*<<< orphan*/  macphymode; void* bandset; void* current_bandtype; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int reg_fwctrl_lps; int reg_max_lps_awakeintvl; int /*<<< orphan*/  fwctrl_psmode; int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  inactiveps; int /*<<< orphan*/  swctrl_lps; } ;
struct TYPE_7__ {int dm_initialgain_enable; int disable_framebursting; int useramask; scalar_t__ thermalvalue; scalar_t__ dm_flag; } ;
struct rtl_priv {int max_fw_size; TYPE_6__ rtlhal; TYPE_5__ io; TYPE_4__ psc; TYPE_3__* cfg; TYPE_1__ dm; } ;
struct rtl_pci {int receive_config; int shortretry_limit; int longretry_limit; int first_init; void** irq_mask; scalar_t__ transmit_config; } ;
struct rt_firmware {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct fw_hdr {int dummy; } ;
struct TYPE_9__ {TYPE_2__* mod_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  fwctrl_lps; int /*<<< orphan*/  swctrl_lps; int /*<<< orphan*/  inactiveps; } ;

/* Variables and functions */
 void* BAND_ON_2_4G ; 
 int /*<<< orphan*/  FW_PS_DTIM_MODE ; 
 int /*<<< orphan*/  FW_PS_MAX_MODE ; 
 int /*<<< orphan*/  FW_PS_MIN_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMR_BCNINT ; 
 int IMR_BDOK ; 
 int IMR_BEDOK ; 
 int IMR_BKDOK ; 
 int IMR_COMDOK ; 
 int IMR_HCCADOK ; 
 int IMR_HIGHDOK ; 
 int IMR_MGNTDOK ; 
 int IMR_RDU ; 
 int IMR_ROK ; 
 int IMR_RXCMDOK ; 
 int IMR_RXFOVW ; 
 int IMR_VIDOK ; 
 int IMR_VODOK ; 
 int RCR_AB ; 
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
 int RCR_APP_PHYST_STAFF ; 
 int RCR_APWRMGT ; 
 int RCR_FIFO_OFFSET ; 
 int RTL8190_MAX_FIRMWARE_CODE_SIZE ; 
 int /*<<< orphan*/  SINGLEMAC_SINGLEPHY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92s_init_aspm_vars (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92se_fw_cb ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

__attribute__((used)) static int rtl92s_init_sw_vars(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	int err = 0;
	u16 earlyrxthreshold = 7;
	char *fw_name = "rtlwifi/rtl8192sefw.bin";

	rtlpriv->dm.dm_initialgain_enable = true;
	rtlpriv->dm.dm_flag = 0;
	rtlpriv->dm.disable_framebursting = false;
	rtlpriv->dm.thermalvalue = 0;
	rtlpriv->dm.useramask = true;

	/* compatible 5G band 91se just 2.4G band & smsp */
	rtlpriv->rtlhal.current_bandtype = BAND_ON_2_4G;
	rtlpriv->rtlhal.bandset = BAND_ON_2_4G;
	rtlpriv->rtlhal.macphymode = SINGLEMAC_SINGLEPHY;

	rtlpci->transmit_config = 0;

	rtlpci->receive_config =
			RCR_APPFCS |
			RCR_APWRMGT |
			/*RCR_ADD3 |*/
			RCR_AMF	|
			RCR_ADF |
			RCR_APP_MIC |
			RCR_APP_ICV |
			RCR_AICV |
			/* Accept ICV error, CRC32 Error */
			RCR_ACRC32 |
			RCR_AB |
			/* Accept Broadcast, Multicast */
			RCR_AM	|
			/* Accept Physical match */
			RCR_APM |
			/* Accept Destination Address packets */
			/*RCR_AAP |*/
			RCR_APP_PHYST_STAFF |
			/* Accept PHY status */
			RCR_APP_PHYST_RXFF |
			(earlyrxthreshold << RCR_FIFO_OFFSET);

	rtlpci->irq_mask[0] = (u32)
			(IMR_ROK |
			IMR_VODOK |
			IMR_VIDOK |
			IMR_BEDOK |
			IMR_BKDOK |
			IMR_HCCADOK |
			IMR_MGNTDOK |
			IMR_COMDOK |
			IMR_HIGHDOK |
			IMR_BDOK |
			IMR_RXCMDOK |
			/*IMR_TIMEOUT0 |*/
			IMR_RDU |
			IMR_RXFOVW	|
			IMR_BCNINT
			/*| IMR_TXFOVW*/
			/*| IMR_TBDOK |
			IMR_TBDER*/);

	rtlpci->irq_mask[1] = (u32) 0;

	rtlpci->shortretry_limit = 0x30;
	rtlpci->longretry_limit = 0x30;

	rtlpci->first_init = true;

	/* for LPS & IPS */
	rtlpriv->psc.inactiveps = rtlpriv->cfg->mod_params->inactiveps;
	rtlpriv->psc.swctrl_lps = rtlpriv->cfg->mod_params->swctrl_lps;
	rtlpriv->psc.fwctrl_lps = rtlpriv->cfg->mod_params->fwctrl_lps;
	if (!rtlpriv->psc.inactiveps)
		pr_info("Power Save off (module option)\n");
	if (!rtlpriv->psc.fwctrl_lps)
		pr_info("FW Power Save off (module option)\n");
	rtlpriv->psc.reg_fwctrl_lps = 3;
	rtlpriv->psc.reg_max_lps_awakeintvl = 5;
	/* for ASPM, you can close aspm through
	 * set const_support_pciaspm = 0 */
	rtl92s_init_aspm_vars(hw);

	if (rtlpriv->psc.reg_fwctrl_lps == 1)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MIN_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 2)
		rtlpriv->psc.fwctrl_psmode = FW_PS_MAX_MODE;
	else if (rtlpriv->psc.reg_fwctrl_lps == 3)
		rtlpriv->psc.fwctrl_psmode = FW_PS_DTIM_MODE;

	/* for firmware buf */
	rtlpriv->rtlhal.pfirmware = vzalloc(sizeof(struct rt_firmware));
	if (!rtlpriv->rtlhal.pfirmware)
		return 1;

	rtlpriv->max_fw_size = RTL8190_MAX_FIRMWARE_CODE_SIZE*2 +
			       sizeof(struct fw_hdr);
	pr_info("Driver for Realtek RTL8192SE/RTL8191SE\n"
		"Loading firmware %s\n", fw_name);
	/* request fw */
	err = request_firmware_nowait(THIS_MODULE, 1, fw_name,
				      rtlpriv->io.dev, GFP_KERNEL, hw,
				      rtl92se_fw_cb);
	if (err) {
		pr_err("Failed to request firmware!\n");
		vfree(rtlpriv->rtlhal.pfirmware);
		rtlpriv->rtlhal.pfirmware = NULL;
		return 1;
	}

	return err;
}