#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {unsigned long txbytesunicast; unsigned long rxbytesunicast; } ;
struct r8192_priv {int bis_cur_rdlstate; int bcurrent_turbo_EDCA; TYPE_4__ stats; TYPE_3__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_qos_parameters {int* aifs; int /*<<< orphan*/ * cw_min; int /*<<< orphan*/ * cw_max; int /*<<< orphan*/ * tx_op_limit; } ;
struct aci_aifsn {scalar_t__ acm; } ;
struct TYPE_10__ {int IOTAction; size_t IOTPeer; } ;
struct TYPE_6__ {struct ieee80211_qos_parameters parameters; } ;
struct TYPE_7__ {TYPE_1__ qos_data; } ;
struct TYPE_8__ {scalar_t__ state; int bis_any_nonbepkts; int mode; TYPE_2__ current_network; TYPE_5__* pHTInfo; } ;
typedef  TYPE_5__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int AC_PARAM_AIFS_OFFSET ; 
 int AC_PARAM_ECW_MAX_OFFSET ; 
 int AC_PARAM_ECW_MIN_OFFSET ; 
 int AC_PARAM_TXOP_LIMIT_OFFSET ; 
 int /*<<< orphan*/  AcmHwCtrl ; 
 int AcmHw_BeqEn ; 
 int /*<<< orphan*/  COMP_QOS ; 
 int /*<<< orphan*/  EDCAPARA_BE ; 
 int HT_IOT_ACT_DISABLE_EDCA_TURBO ; 
 scalar_t__ IEEE80211_LINKED ; 
 int IEEE_G ; 
 int IEEE_N_24G ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int aSifsTime ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int /*<<< orphan*/  dm_init_edca_turbo (struct net_device*) ; 
 int* edca_setting_DL ; 
 int* edca_setting_UL ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_check_edca_turbo(
	struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	/*PSTA_QOS			pStaQos = pMgntInfo->pStaQos;*/

	/* Keep past Tx/Rx packet count for RT-to-RT EDCA turbo. */
	static unsigned long			lastTxOkCnt;
	static unsigned long			lastRxOkCnt;
	unsigned long				curTxOkCnt = 0;
	unsigned long				curRxOkCnt = 0;

	/* Do not be Turbo if it's under WiFi config and Qos Enabled, because the EDCA parameters
	 * should follow the settings from QAP. By Bruce, 2007-12-07.
	 */
	if (priv->ieee80211->state != IEEE80211_LINKED)
		goto dm_CheckEdcaTurbo_EXIT;
	/* We do not turn on EDCA turbo mode for some AP that has IOT issue */
	if (priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_EDCA_TURBO)
		goto dm_CheckEdcaTurbo_EXIT;

	/*printk("========>%s():bis_any_nonbepkts is %d\n", __func__, priv->bis_any_nonbepkts);*/
	/* Check the status for current condition. */
	if (!priv->ieee80211->bis_any_nonbepkts) {
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		/* For RT-AP, we needs to turn it on when Rx>Tx */
		if (curRxOkCnt > 4*curTxOkCnt) {
			/*printk("%s():curRxOkCnt > 4*curTxOkCnt\n");*/
			if (!priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA) {
				write_nic_dword(dev, EDCAPARA_BE, edca_setting_DL[pHTInfo->IOTPeer]);
				priv->bis_cur_rdlstate = true;
			}
		} else {
			/*printk("%s():curRxOkCnt < 4*curTxOkCnt\n");*/
			if (priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA) {
				write_nic_dword(dev, EDCAPARA_BE, edca_setting_UL[pHTInfo->IOTPeer]);
				priv->bis_cur_rdlstate = false;
			}

		}

		priv->bcurrent_turbo_EDCA = true;
	} else {
		/* Turn Off EDCA turbo here.
		 * Restore original EDCA according to the declaration of AP.
		 */
		if (priv->bcurrent_turbo_EDCA) {
			u8	u1bAIFS;
			u32	u4bAcParam, op_limit, cw_max, cw_min;

			struct ieee80211_qos_parameters *qos_parameters = &priv->ieee80211->current_network.qos_data.parameters;
			u8 mode = priv->ieee80211->mode;

			/*  For Each time updating EDCA parameter, reset EDCA turbo mode status. */
			dm_init_edca_turbo(dev);

			u1bAIFS = qos_parameters->aifs[0] * ((mode & (IEEE_G | IEEE_N_24G)) ? 9 : 20) + aSifsTime;

			op_limit = (u32)le16_to_cpu(qos_parameters->tx_op_limit[0]);
			cw_max   = (u32)le16_to_cpu(qos_parameters->cw_max[0]);
			cw_min   = (u32)le16_to_cpu(qos_parameters->cw_min[0]);

			op_limit <<= AC_PARAM_TXOP_LIMIT_OFFSET;
			cw_max   <<= AC_PARAM_ECW_MAX_OFFSET;
			cw_min   <<= AC_PARAM_ECW_MIN_OFFSET;
			u1bAIFS  <<= AC_PARAM_AIFS_OFFSET;

			u4bAcParam = op_limit | cw_max | cw_min | u1bAIFS;
			cpu_to_le32s(&u4bAcParam);

			write_nic_dword(dev, EDCAPARA_BE, u4bAcParam);


			/* Check ACM bit.
			 * If it is set, immediately set ACM control bit to downgrading AC for passing WMM testplan. Annie, 2005-12-13.
			 */
			{
				/*  TODO:  Modified this part and try to set acm control in only 1 IO processing!! */

				struct aci_aifsn *pAciAifsn = (struct aci_aifsn *)&(qos_parameters->aifs[0]);
				u8		AcmCtrl;

				read_nic_byte(dev, AcmHwCtrl, &AcmCtrl);

				if (pAciAifsn->acm) { /*  acm bit is 1. */
					AcmCtrl |= AcmHw_BeqEn;
				} else {	/* ACM bit is 0. */
					AcmCtrl &= (~AcmHw_BeqEn);
				}

				RT_TRACE(COMP_QOS, "SetHwReg8190pci(): [HW_VAR_ACM_CTRL] Write 0x%X\n", AcmCtrl);
				write_nic_byte(dev, AcmHwCtrl, AcmCtrl);
			}
			priv->bcurrent_turbo_EDCA = false;
		}
	}

dm_CheckEdcaTurbo_EXIT:
	/* Set variables for next time. */
	priv->ieee80211->bis_any_nonbepkts = false;
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
}