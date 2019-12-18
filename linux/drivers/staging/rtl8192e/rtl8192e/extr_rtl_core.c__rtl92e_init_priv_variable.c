#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sw_cam_table {int dummy; } ;
struct rt_firmware {int dummy; } ;
struct r8192_priv {int up_first_time; int blinked_ingpio; int bDriverIsGoingToUnload; int being_init_adapter; int initialized_at_probe; int bdisable_nic; int bfirst_init; int txringcount; int rxbuffersize; int chan; int RegChannelPlan; int promisc; int bcck_in_ch14; int bfsync_processing; int CckPwEnl; int ScanDelay; int bForcedSilentReset; int bDisableNormalResetCheck; int force_reset; int bHwRadioOff; int RegRfOff; int isRFOff; int bInPowerSaveMode; int RFChangeInProgress; int SetRFPowerStateInProgress; TYPE_4__* rtllib; int /*<<< orphan*/  skb_queue; int /*<<< orphan*/  pFirmware; int /*<<< orphan*/  card_type; scalar_t__ bHwRfOffAction; scalar_t__ RxCounter; int /*<<< orphan*/  InterruptLog; int /*<<< orphan*/  ResetProgress; scalar_t__ rfc_txpowertrackingindex; scalar_t__ rfa_txpowertrackingindex; scalar_t__ CCKPresentAttentuation; int /*<<< orphan*/  retry_data; int /*<<< orphan*/  retry_rts; scalar_t__ irq_enabled; int /*<<< orphan*/  rxringcount; scalar_t__ polling_timer_on; int /*<<< orphan*/  dot11CurrentPreambleMode; int /*<<< orphan*/  AcmMethod; } ;
struct net_device {int flags; } ;
struct log_int_8190 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  beacon_interval; } ;
struct TYPE_5__ {int bInactivePs; int bIPSModeBackup; int bLeisurePs; int bFwCtrlLPS; } ;
struct TYPE_7__ {int bPromiscuousOn; int bFilterSourceStationFrame; } ;
struct TYPE_8__ {int bNetPromiscuousMode; int rate; int short_slot; int active_scan; int be_scan_inprogress; int modulation; int host_encrypt; int host_decrypt; int /*<<< orphan*/ * skb_aggQ; int /*<<< orphan*/ * skb_waitQ; int /*<<< orphan*/  fts; void* iw_mode; TYPE_2__ current_network; int /*<<< orphan*/  eRFPowerState; int /*<<< orphan*/  sta_sleep; scalar_t__ LPSDelayCnt; TYPE_1__ PowerSaveControl; scalar_t__ RfOffReason; scalar_t__ wx_set_enc; int /*<<< orphan*/ * swcamtable; int /*<<< orphan*/  rts; scalar_t__ ieee_up; TYPE_3__ IntelPromiscuousModeInfo; int /*<<< orphan*/  mode; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BEACONINTERVAL ; 
 int /*<<< orphan*/  DEFAULT_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_RETRY_DATA ; 
 int /*<<< orphan*/  DEFAULT_RETRY_RTS ; 
 int /*<<< orphan*/  DEFAULT_RTS_THRESHOLD ; 
 int IFF_PROMISC ; 
 void* IW_MODE_INFRA ; 
 int /*<<< orphan*/  LPS_IS_WAKE ; 
 size_t MAX_QUEUE_SIZE ; 
 int /*<<< orphan*/  MAX_RX_COUNT ; 
 int /*<<< orphan*/  PCI ; 
 int /*<<< orphan*/  PREAMBLE_AUTO ; 
 int /*<<< orphan*/  RESET_TYPE_NORESET ; 
 int RTLLIB_CCK_MODULATION ; 
 int RTLLIB_OFDM_MODULATION ; 
 int /*<<< orphan*/  WIRELESS_MODE_AUTO ; 
 int /*<<< orphan*/  eAcmWay2_SW ; 
 int /*<<< orphan*/  eRfOn ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

__attribute__((used)) static void _rtl92e_init_priv_variable(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	u8 i;

	priv->AcmMethod = eAcmWay2_SW;
	priv->dot11CurrentPreambleMode = PREAMBLE_AUTO;
	priv->rtllib->status = 0;
	priv->polling_timer_on = 0;
	priv->up_first_time = 1;
	priv->blinked_ingpio = false;
	priv->bDriverIsGoingToUnload = false;
	priv->being_init_adapter = false;
	priv->initialized_at_probe = false;
	priv->bdisable_nic = false;
	priv->bfirst_init = false;
	priv->txringcount = 64;
	priv->rxbuffersize = 9100;
	priv->rxringcount = MAX_RX_COUNT;
	priv->irq_enabled = 0;
	priv->chan = 1;
	priv->RegChannelPlan = 0xf;
	priv->rtllib->mode = WIRELESS_MODE_AUTO;
	priv->rtllib->iw_mode = IW_MODE_INFRA;
	priv->rtllib->bNetPromiscuousMode = false;
	priv->rtllib->IntelPromiscuousModeInfo.bPromiscuousOn = false;
	priv->rtllib->IntelPromiscuousModeInfo.bFilterSourceStationFrame =
								 false;
	priv->rtllib->ieee_up = 0;
	priv->retry_rts = DEFAULT_RETRY_RTS;
	priv->retry_data = DEFAULT_RETRY_DATA;
	priv->rtllib->rts = DEFAULT_RTS_THRESHOLD;
	priv->rtllib->rate = 110;
	priv->rtllib->short_slot = 1;
	priv->promisc = (dev->flags & IFF_PROMISC) ? 1 : 0;
	priv->bcck_in_ch14 = false;
	priv->bfsync_processing  = false;
	priv->CCKPresentAttentuation = 0;
	priv->rfa_txpowertrackingindex = 0;
	priv->rfc_txpowertrackingindex = 0;
	priv->CckPwEnl = 6;
	priv->ScanDelay = 50;
	priv->ResetProgress = RESET_TYPE_NORESET;
	priv->bForcedSilentReset = false;
	priv->bDisableNormalResetCheck = false;
	priv->force_reset = false;
	memset(priv->rtllib->swcamtable, 0, sizeof(struct sw_cam_table) * 32);

	memset(&priv->InterruptLog, 0, sizeof(struct log_int_8190));
	priv->RxCounter = 0;
	priv->rtllib->wx_set_enc = 0;
	priv->bHwRadioOff = false;
	priv->RegRfOff = false;
	priv->isRFOff = false;
	priv->bInPowerSaveMode = false;
	priv->rtllib->RfOffReason = 0;
	priv->RFChangeInProgress = false;
	priv->bHwRfOffAction = 0;
	priv->SetRFPowerStateInProgress = false;
	priv->rtllib->PowerSaveControl.bInactivePs = true;
	priv->rtllib->PowerSaveControl.bIPSModeBackup = false;
	priv->rtllib->PowerSaveControl.bLeisurePs = true;
	priv->rtllib->PowerSaveControl.bFwCtrlLPS = false;
	priv->rtllib->LPSDelayCnt = 0;
	priv->rtllib->sta_sleep = LPS_IS_WAKE;
	priv->rtllib->eRFPowerState = eRfOn;

	priv->rtllib->current_network.beacon_interval = DEFAULT_BEACONINTERVAL;
	priv->rtllib->iw_mode = IW_MODE_INFRA;
	priv->rtllib->active_scan = 1;
	priv->rtllib->be_scan_inprogress = false;
	priv->rtllib->modulation = RTLLIB_CCK_MODULATION |
				   RTLLIB_OFDM_MODULATION;
	priv->rtllib->host_encrypt = 1;
	priv->rtllib->host_decrypt = 1;

	priv->rtllib->fts = DEFAULT_FRAG_THRESHOLD;

	priv->card_type = PCI;

	priv->pFirmware = vzalloc(sizeof(struct rt_firmware));
	if (!priv->pFirmware)
		netdev_err(dev,
			   "rtl8192e: Unable to allocate space for firmware\n");

	skb_queue_head_init(&priv->skb_queue);

	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->rtllib->skb_waitQ[i]);
	for (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_head_init(&priv->rtllib->skb_aggQ[i]);
}