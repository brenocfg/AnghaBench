#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ valid; } ;
struct tx_ts_record {TYPE_1__ tx_pending_ba_record; TYPE_1__ tx_admitted_ba_record; } ;
struct ts_common_info {int /*<<< orphan*/  addr; } ;
struct rx_ts_record {TYPE_1__ rx_admitted_ba_record; } ;
struct ieee80211_device {int dummy; } ;
typedef  enum tr_select { ____Placeholder_tr_select } tr_select ;

/* Variables and functions */
 int /*<<< orphan*/  DELBA_REASON_END_BA ; 
 int RX_DIR ; 
 scalar_t__ RxTsDeleteBA (struct ieee80211_device*,struct rx_ts_record*) ; 
 int TX_DIR ; 
 scalar_t__ TxTsDeleteBA (struct ieee80211_device*,struct tx_ts_record*) ; 
 int /*<<< orphan*/  ieee80211_send_DELBA (struct ieee80211_device*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
TsInitDelBA(struct ieee80211_device *ieee, struct ts_common_info *pTsCommonInfo, enum tr_select TxRxSelect)
{
	if (TxRxSelect == TX_DIR) {
		struct tx_ts_record *pTxTs = (struct tx_ts_record *)pTsCommonInfo;

		if (TxTsDeleteBA(ieee, pTxTs))
			ieee80211_send_DELBA(
				ieee,
				pTsCommonInfo->addr,
				(pTxTs->tx_admitted_ba_record.valid) ? (&pTxTs->tx_admitted_ba_record) : (&pTxTs->tx_pending_ba_record),
				TxRxSelect,
				DELBA_REASON_END_BA);
	} else if (TxRxSelect == RX_DIR) {
		struct rx_ts_record *pRxTs = (struct rx_ts_record *)pTsCommonInfo;
		if (RxTsDeleteBA(ieee, pRxTs))
			ieee80211_send_DELBA(
				ieee,
				pTsCommonInfo->addr,
				&pRxTs->rx_admitted_ba_record,
				TxRxSelect,
				DELBA_REASON_END_BA);
	}
}