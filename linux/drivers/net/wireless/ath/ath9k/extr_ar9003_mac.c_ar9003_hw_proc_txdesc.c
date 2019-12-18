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
typedef  int u32 ;
struct ath_tx_status {int ts_rateindex; int ts_seqnum; int tid; int qid; int desc_id; int ts_rssi_ctl0; int ts_rssi_ctl1; int ts_rssi_ctl2; int ts_shortretry; int ts_longretry; int ts_virtcol; int ts_rssi; int ts_rssi_ext0; int ts_rssi_ext1; int ts_rssi_ext2; int /*<<< orphan*/  ts_flags; int /*<<< orphan*/  ts_status; int /*<<< orphan*/  ba_high; int /*<<< orphan*/  ba_low; int /*<<< orphan*/  ts_tstamp; } ;
struct ath_hw {size_t ts_tail; int ts_size; struct ar9003_txs* ts_ring; } ;
struct ar9003_txs {int ds_info; int status1; int /*<<< orphan*/  status7; int /*<<< orphan*/  status3; int /*<<< orphan*/  status6; int /*<<< orphan*/  status5; int /*<<< orphan*/  status2; int /*<<< orphan*/  status4; int /*<<< orphan*/  status8; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DataFailCnt ; 
 int AR_DescCfgErr ; 
 int /*<<< orphan*/  AR_DescId ; 
 int AR_ExcessiveRetries ; 
 int AR_FIFOUnderrun ; 
 int AR_Filtered ; 
 int /*<<< orphan*/  AR_FinalTxIdx ; 
 int /*<<< orphan*/  AR_RTSFailCnt ; 
 int /*<<< orphan*/  AR_SeqNum ; 
 int AR_TxBaStatus ; 
 int AR_TxDataUnderrun ; 
 int AR_TxDelimUnderrun ; 
 int /*<<< orphan*/  AR_TxDescId ; 
 int AR_TxDone ; 
 int AR_TxOpExceeded ; 
 int /*<<< orphan*/  AR_TxQcuNum ; 
 int /*<<< orphan*/  AR_TxRSSIAnt00 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt01 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt02 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt10 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt11 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt12 ; 
 int /*<<< orphan*/  AR_TxRSSICombined ; 
 int /*<<< orphan*/  AR_TxRxDesc ; 
 int /*<<< orphan*/  AR_TxTid ; 
 int AR_TxTimerExpired ; 
 int /*<<< orphan*/  AR_VirtRetryCnt ; 
 int /*<<< orphan*/  ATH9K_TXERR_FIFO ; 
 int /*<<< orphan*/  ATH9K_TXERR_FILT ; 
 int /*<<< orphan*/  ATH9K_TXERR_TIMER_EXPIRED ; 
 int /*<<< orphan*/  ATH9K_TXERR_XRETRY ; 
 int /*<<< orphan*/  ATH9K_TXERR_XTXOP ; 
 int /*<<< orphan*/  ATH9K_TX_BA ; 
 int /*<<< orphan*/  ATH9K_TX_DATA_UNDERRUN ; 
 int /*<<< orphan*/  ATH9K_TX_DELIM_UNDERRUN ; 
 int /*<<< orphan*/  ATH9K_TX_DESC_CFG_ERR ; 
 int ATHEROS_VENDOR_ID ; 
 int EINPROGRESS ; 
 int EIO ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMIT ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_updatetxtriglevel (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct ar9003_txs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar9003_hw_proc_txdesc(struct ath_hw *ah, void *ds,
				 struct ath_tx_status *ts)
{
	struct ar9003_txs *ads;
	u32 status;

	ads = &ah->ts_ring[ah->ts_tail];

	status = READ_ONCE(ads->status8);
	if ((status & AR_TxDone) == 0)
		return -EINPROGRESS;

	ah->ts_tail = (ah->ts_tail + 1) % ah->ts_size;

	if ((MS(ads->ds_info, AR_DescId) != ATHEROS_VENDOR_ID) ||
	    (MS(ads->ds_info, AR_TxRxDesc) != 1)) {
		ath_dbg(ath9k_hw_common(ah), XMIT,
			"Tx Descriptor error %x\n", ads->ds_info);
		memset(ads, 0, sizeof(*ads));
		return -EIO;
	}

	ts->ts_rateindex = MS(status, AR_FinalTxIdx);
	ts->ts_seqnum = MS(status, AR_SeqNum);
	ts->tid = MS(status, AR_TxTid);

	ts->qid = MS(ads->ds_info, AR_TxQcuNum);
	ts->desc_id = MS(ads->status1, AR_TxDescId);
	ts->ts_tstamp = ads->status4;
	ts->ts_status = 0;
	ts->ts_flags  = 0;

	if (status & AR_TxOpExceeded)
		ts->ts_status |= ATH9K_TXERR_XTXOP;
	status = READ_ONCE(ads->status2);
	ts->ts_rssi_ctl0 = MS(status, AR_TxRSSIAnt00);
	ts->ts_rssi_ctl1 = MS(status, AR_TxRSSIAnt01);
	ts->ts_rssi_ctl2 = MS(status, AR_TxRSSIAnt02);
	if (status & AR_TxBaStatus) {
		ts->ts_flags |= ATH9K_TX_BA;
		ts->ba_low = ads->status5;
		ts->ba_high = ads->status6;
	}

	status = READ_ONCE(ads->status3);
	if (status & AR_ExcessiveRetries)
		ts->ts_status |= ATH9K_TXERR_XRETRY;
	if (status & AR_Filtered)
		ts->ts_status |= ATH9K_TXERR_FILT;
	if (status & AR_FIFOUnderrun) {
		ts->ts_status |= ATH9K_TXERR_FIFO;
		ath9k_hw_updatetxtriglevel(ah, true);
	}
	if (status & AR_TxTimerExpired)
		ts->ts_status |= ATH9K_TXERR_TIMER_EXPIRED;
	if (status & AR_DescCfgErr)
		ts->ts_flags |= ATH9K_TX_DESC_CFG_ERR;
	if (status & AR_TxDataUnderrun) {
		ts->ts_flags |= ATH9K_TX_DATA_UNDERRUN;
		ath9k_hw_updatetxtriglevel(ah, true);
	}
	if (status & AR_TxDelimUnderrun) {
		ts->ts_flags |= ATH9K_TX_DELIM_UNDERRUN;
		ath9k_hw_updatetxtriglevel(ah, true);
	}
	ts->ts_shortretry = MS(status, AR_RTSFailCnt);
	ts->ts_longretry = MS(status, AR_DataFailCnt);
	ts->ts_virtcol = MS(status, AR_VirtRetryCnt);

	status = READ_ONCE(ads->status7);
	ts->ts_rssi = MS(status, AR_TxRSSICombined);
	ts->ts_rssi_ext0 = MS(status, AR_TxRSSIAnt10);
	ts->ts_rssi_ext1 = MS(status, AR_TxRSSIAnt11);
	ts->ts_rssi_ext2 = MS(status, AR_TxRSSIAnt12);

	memset(ads, 0, sizeof(*ads));

	return 0;
}