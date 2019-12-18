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
struct TYPE_5__ {int /*<<< orphan*/  seq_num; } ;
struct TYPE_6__ {TYPE_1__ field; } ;
struct TYPE_7__ {TYPE_2__ start_seq_ctrl; int /*<<< orphan*/  valid; } ;
struct tx_ts_record {int using_ba; int tx_cur_seq; TYPE_3__ tx_admitted_ba_record; } ;
struct ts_common_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct rtl_80211_hdr_1addr {int /*<<< orphan*/  addr1; } ;
struct ieee80211_device {scalar_t__ iw_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* GetNmodeSupportBySecCfg ) (int /*<<< orphan*/ ) ;TYPE_4__* pHTInfo; } ;
struct cb_desc {int bAMPDUEnable; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  ampdu_density; } ;
struct TYPE_8__ {int ForcedAMPDUMode; int /*<<< orphan*/  ForcedAMPDUFactor; int /*<<< orphan*/  ForcedMPDUDensity; int /*<<< orphan*/  CurrentMPDUDensity; int /*<<< orphan*/  CurrentAMPDUFactor; scalar_t__ bCurrentAMPDUEnable; int /*<<< orphan*/  bEnableHT; int /*<<< orphan*/  bCurrentHTSupport; } ;
typedef  TYPE_4__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/  GetTs (struct ieee80211_device*,struct ts_common_info**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  HT_AGG_AUTO 130 
#define  HT_AGG_FORCE_DISABLE 129 
#define  HT_AGG_FORCE_ENABLE 128 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  IsQoSDataFrame (scalar_t__) ; 
 scalar_t__ SN_LESS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_DIR ; 
 int /*<<< orphan*/  TsStartAddBaProcess (struct ieee80211_device*,struct tx_ts_record*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_tx_query_agg_cap(struct ieee80211_device *ieee,
				       struct sk_buff *skb, struct cb_desc *tcb_desc)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	struct tx_ts_record        *pTxTs = NULL;
	struct rtl_80211_hdr_1addr *hdr = (struct rtl_80211_hdr_1addr *)skb->data;

	if (!pHTInfo->bCurrentHTSupport || !pHTInfo->bEnableHT)
		return;
	if (!IsQoSDataFrame(skb->data))
		return;

	if (is_multicast_ether_addr(hdr->addr1))
		return;
	//check packet and mode later
	if (!ieee->GetNmodeSupportBySecCfg(ieee->dev)) {
		return;
	}
	if (pHTInfo->bCurrentAMPDUEnable) {
		if (!GetTs(ieee, (struct ts_common_info **)(&pTxTs), hdr->addr1, skb->priority, TX_DIR, true)) {
			printk("===>can't get TS\n");
			return;
		}
		if (!pTxTs->tx_admitted_ba_record.valid) {
			TsStartAddBaProcess(ieee, pTxTs);
			goto FORCED_AGG_SETTING;
		} else if (!pTxTs->using_ba) {
			if (SN_LESS(pTxTs->tx_admitted_ba_record.start_seq_ctrl.field.seq_num, (pTxTs->tx_cur_seq + 1) % 4096))
				pTxTs->using_ba = true;
			else
				goto FORCED_AGG_SETTING;
		}

		if (ieee->iw_mode == IW_MODE_INFRA) {
			tcb_desc->bAMPDUEnable = true;
			tcb_desc->ampdu_factor = pHTInfo->CurrentAMPDUFactor;
			tcb_desc->ampdu_density = pHTInfo->CurrentMPDUDensity;
		}
	}
FORCED_AGG_SETTING:
	switch (pHTInfo->ForcedAMPDUMode) {
		case HT_AGG_AUTO:
			break;

		case HT_AGG_FORCE_ENABLE:
			tcb_desc->bAMPDUEnable = true;
			tcb_desc->ampdu_density = pHTInfo->ForcedMPDUDensity;
			tcb_desc->ampdu_factor = pHTInfo->ForcedAMPDUFactor;
			break;

		case HT_AGG_FORCE_DISABLE:
			tcb_desc->bAMPDUEnable = false;
			tcb_desc->ampdu_density = 0;
			tcb_desc->ampdu_factor = 0;
			break;

	}
		return;
}