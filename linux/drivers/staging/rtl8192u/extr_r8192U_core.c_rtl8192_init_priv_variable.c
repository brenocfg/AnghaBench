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
typedef  size_t u8 ;
typedef  int u32 ;
struct r8192_priv {int chan; int promisc; int CckPwEnl; int IrpPendingCount; int bForcedSilentReset; int bDisableNormalResetCheck; int force_reset; int ShortRetryLimit; int LongRetryLimit; int EarlyRxThreshold; int TransmitConfig; int ReceiveConfig; int /*<<< orphan*/  rf_set_chan; TYPE_2__* ieee80211; int /*<<< orphan*/  skb_queue; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  pFirmware; scalar_t__ AcmControl; scalar_t__ enable_gpio0; int /*<<< orphan*/  card_type; int /*<<< orphan*/  ResetProgress; int /*<<< orphan*/  retry_data; int /*<<< orphan*/  retry_rts; int /*<<< orphan*/  card_8192; } ;
struct net_device {int flags; } ;
typedef  int /*<<< orphan*/  rt_firmware ;
struct TYPE_3__ {int /*<<< orphan*/  beacon_interval; } ;
struct TYPE_4__ {int rate; int short_slot; int softmac_features; int active_scan; int modulation; int host_encrypt; int host_decrypt; int qos_support; int /*<<< orphan*/ * skb_drv_aggQ; int /*<<< orphan*/ * skb_aggQ; int /*<<< orphan*/ * skb_waitQ; int /*<<< orphan*/  InitialGainHandler; int /*<<< orphan*/  SetWirelessMode; int /*<<< orphan*/  GetHalfNmodeSupportByAPsHandler; int /*<<< orphan*/  GetNmodeSupportBySecCfg; int /*<<< orphan*/  handle_beacon; int /*<<< orphan*/  handle_assoc_response; int /*<<< orphan*/  SetBWModeHandler; int /*<<< orphan*/  tx_headroom; int /*<<< orphan*/  check_nic_enough_desc; int /*<<< orphan*/  fts; scalar_t__ init_wmmparam_flag; int /*<<< orphan*/  data_hard_resume; int /*<<< orphan*/  data_hard_stop; int /*<<< orphan*/  softmac_data_hard_start_xmit; int /*<<< orphan*/  link_change; int /*<<< orphan*/  set_chan; int /*<<< orphan*/  softmac_hard_start_xmit; int /*<<< orphan*/ * stop_send_beacons; int /*<<< orphan*/ * start_send_beacons; TYPE_1__ current_network; scalar_t__ FwRWRF; int /*<<< orphan*/  rts; scalar_t__ ieee_up; int /*<<< orphan*/  iw_mode; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BEACONINTERVAL ; 
 int /*<<< orphan*/  DEFAULT_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_RETRY_DATA ; 
 int /*<<< orphan*/  DEFAULT_RETRY_RTS ; 
 int /*<<< orphan*/  DEFAULT_RTS_THRESHOLD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GetHalfNmodeSupportByAPs819xUsb ; 
 int /*<<< orphan*/  GetNmodeSupportBySecCfg8192 ; 
 int IEEE80211_CCK_MODULATION ; 
 int IEEE80211_OFDM_MODULATION ; 
 int IEEE_SOFTMAC_ASSOCIATE ; 
 int IEEE_SOFTMAC_BEACONS ; 
 int IEEE_SOFTMAC_PROBERQ ; 
 int IEEE_SOFTMAC_PROBERS ; 
 int IEEE_SOFTMAC_SCAN ; 
 int IEEE_SOFTMAC_TX_QUEUE ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  InitialGain819xUsb ; 
 size_t MAX_QUEUE_SIZE ; 
 int /*<<< orphan*/  NIC_8192U ; 
 int RCR_AB ; 
 int RCR_ACF ; 
 int RCR_ADF ; 
 int RCR_AM ; 
 int RCR_AMF ; 
 int RCR_APM ; 
 int RCR_MXDMA_OFFSET ; 
 int RCR_ONLYERLPKT ; 
 int /*<<< orphan*/  RESET_TYPE_NORESET ; 
 int RX_FIFO_THRESHOLD_SHIFT ; 
 int TCR_LRL_OFFSET ; 
 int TCR_MXDMA_2048 ; 
 int TCR_MXDMA_OFFSET ; 
 int TCR_SAT ; 
 int TCR_SRL_OFFSET ; 
 int /*<<< orphan*/  TX_PACKET_SHIFT_BYTES ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  WIRELESS_MODE_AUTO ; 
 int /*<<< orphan*/  check_nic_enough_desc ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_SetBWMode ; 
 int /*<<< orphan*/  rtl8192_SetWirelessMode ; 
 int /*<<< orphan*/  rtl8192_data_hard_resume ; 
 int /*<<< orphan*/  rtl8192_data_hard_stop ; 
 int /*<<< orphan*/  rtl8192_handle_assoc_response ; 
 int /*<<< orphan*/  rtl8192_handle_beacon ; 
 int /*<<< orphan*/  rtl8192_hard_data_xmit ; 
 int /*<<< orphan*/  rtl8192_hard_start_xmit ; 
 int /*<<< orphan*/  rtl8192_link_change ; 
 int /*<<< orphan*/  rtl8192_phy_SwChnl ; 
 int /*<<< orphan*/  rtl8192_set_chan ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtl8192_init_priv_variable(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8 i;

	priv->card_8192 = NIC_8192U;
	priv->chan = 1; /* set to channel 1 */
	priv->ieee80211->mode = WIRELESS_MODE_AUTO; /* SET AUTO */
	priv->ieee80211->iw_mode = IW_MODE_INFRA;
	priv->ieee80211->ieee_up = 0;
	priv->retry_rts = DEFAULT_RETRY_RTS;
	priv->retry_data = DEFAULT_RETRY_DATA;
	priv->ieee80211->rts = DEFAULT_RTS_THRESHOLD;
	priv->ieee80211->rate = 110; /* 11 mbps */
	priv->ieee80211->short_slot = 1;
	priv->promisc = (dev->flags & IFF_PROMISC) ? 1 : 0;
	priv->CckPwEnl = 6;
	/* for silent reset */
	priv->IrpPendingCount = 1;
	priv->ResetProgress = RESET_TYPE_NORESET;
	priv->bForcedSilentReset = false;
	priv->bDisableNormalResetCheck = false;
	priv->force_reset = false;

	/* we don't use FW read/write RF until stable firmware is available. */
	priv->ieee80211->FwRWRF = 0;
	priv->ieee80211->current_network.beacon_interval =
		DEFAULT_BEACONINTERVAL;
	priv->ieee80211->softmac_features  = IEEE_SOFTMAC_SCAN |
		IEEE_SOFTMAC_ASSOCIATE | IEEE_SOFTMAC_PROBERQ |
		IEEE_SOFTMAC_PROBERS | IEEE_SOFTMAC_TX_QUEUE |
		IEEE_SOFTMAC_BEACONS;

	priv->ieee80211->active_scan = 1;
	priv->ieee80211->modulation =
		IEEE80211_CCK_MODULATION | IEEE80211_OFDM_MODULATION;
	priv->ieee80211->host_encrypt = 1;
	priv->ieee80211->host_decrypt = 1;
	priv->ieee80211->start_send_beacons = NULL;
	priv->ieee80211->stop_send_beacons = NULL;
	priv->ieee80211->softmac_hard_start_xmit = rtl8192_hard_start_xmit;
	priv->ieee80211->set_chan = rtl8192_set_chan;
	priv->ieee80211->link_change = rtl8192_link_change;
	priv->ieee80211->softmac_data_hard_start_xmit = rtl8192_hard_data_xmit;
	priv->ieee80211->data_hard_stop = rtl8192_data_hard_stop;
	priv->ieee80211->data_hard_resume = rtl8192_data_hard_resume;
	priv->ieee80211->init_wmmparam_flag = 0;
	priv->ieee80211->fts = DEFAULT_FRAG_THRESHOLD;
	priv->ieee80211->check_nic_enough_desc = check_nic_enough_desc;
	priv->ieee80211->tx_headroom = TX_PACKET_SHIFT_BYTES;
	priv->ieee80211->qos_support = 1;

	priv->ieee80211->SetBWModeHandler = rtl8192_SetBWMode;
	priv->ieee80211->handle_assoc_response = rtl8192_handle_assoc_response;
	priv->ieee80211->handle_beacon = rtl8192_handle_beacon;

	priv->ieee80211->GetNmodeSupportBySecCfg = GetNmodeSupportBySecCfg8192;
	priv->ieee80211->GetHalfNmodeSupportByAPsHandler =
		GetHalfNmodeSupportByAPs819xUsb;
	priv->ieee80211->SetWirelessMode = rtl8192_SetWirelessMode;

	priv->ieee80211->InitialGainHandler = InitialGain819xUsb;
	priv->card_type = USB;
	priv->ShortRetryLimit = 0x30;
	priv->LongRetryLimit = 0x30;
	priv->EarlyRxThreshold = 7;
	priv->enable_gpio0 = 0;
	priv->TransmitConfig =
		/* Max DMA Burst Size per Tx DMA Burst, 7: reserved. */
		(TCR_MXDMA_2048 << TCR_MXDMA_OFFSET)	  |
		/* Short retry limit */
		(priv->ShortRetryLimit << TCR_SRL_OFFSET) |
		/* Long retry limit */
		(priv->LongRetryLimit << TCR_LRL_OFFSET)  |
		/* FALSE: HW provides PLCP length and LENGEXT
		 * TRUE: SW provides them
		 */
		(false ? TCR_SAT : 0);
	priv->ReceiveConfig	=
		/* accept management/data */
		RCR_AMF | RCR_ADF |
		/* accept control frame for SW AP needs PS-poll */
		RCR_ACF |
		/* accept BC/MC/UC */
		RCR_AB | RCR_AM | RCR_APM |
		/* Max DMA Burst Size per Rx DMA Burst, 7: unlimited. */
		((u32)7 << RCR_MXDMA_OFFSET) |
		/* Rx FIFO Threshold, 7: No Rx threshold. */
		(priv->EarlyRxThreshold << RX_FIFO_THRESHOLD_SHIFT) |
		(priv->EarlyRxThreshold == 7 ? RCR_ONLYERLPKT : 0);

	priv->AcmControl = 0;
	priv->pFirmware = kzalloc(sizeof(rt_firmware), GFP_KERNEL);
	if (!priv->pFirmware)
		return -ENOMEM;

	/* rx related queue */
	skb_queue_head_init(&priv->rx_queue);
	skb_queue_head_init(&priv->skb_queue);

	/* Tx related queue */
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->ieee80211->skb_waitQ[i]);
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->ieee80211->skb_aggQ[i]);
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->ieee80211->skb_drv_aggQ[i]);
	priv->rf_set_chan = rtl8192_phy_SwChnl;

	return 0;
}