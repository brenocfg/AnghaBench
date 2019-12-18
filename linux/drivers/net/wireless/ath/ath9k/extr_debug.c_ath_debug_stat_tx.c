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
struct ath_txq {int axq_qnum; } ;
struct ath_tx_status {int ts_status; int ts_flags; } ;
struct TYPE_6__ {TYPE_1__* txstats; } ;
struct TYPE_7__ {TYPE_2__ stats; } ;
struct ath_softc {TYPE_3__ debug; } ;
struct ath_buf {TYPE_4__* bf_mpdu; } ;
struct TYPE_8__ {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes_all; } ;

/* Variables and functions */
 int ATH9K_TXERR_FIFO ; 
 int ATH9K_TXERR_FILT ; 
 int ATH9K_TXERR_TIMER_EXPIRED ; 
 int ATH9K_TXERR_XRETRY ; 
 int ATH9K_TXERR_XTXOP ; 
 int ATH9K_TX_DATA_UNDERRUN ; 
 int ATH9K_TX_DELIM_UNDERRUN ; 
 int ATH9K_TX_DESC_CFG_ERR ; 
 unsigned int ATH_TX_ERROR ; 
 int /*<<< orphan*/  TX_STAT_INC (struct ath_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_completed ; 
 int /*<<< orphan*/  a_xretries ; 
 scalar_t__ bf_isampdu (struct ath_buf*) ; 
 int /*<<< orphan*/  completed ; 
 int /*<<< orphan*/  data_underrun ; 
 int /*<<< orphan*/  delim_underrun ; 
 int /*<<< orphan*/  desc_cfg_err ; 
 int /*<<< orphan*/  fifo_underrun ; 
 int /*<<< orphan*/  timer_exp ; 
 int /*<<< orphan*/  tx_pkts_all ; 
 int /*<<< orphan*/  txerr_filtered ; 
 int /*<<< orphan*/  xretries ; 
 int /*<<< orphan*/  xtxop ; 

void ath_debug_stat_tx(struct ath_softc *sc, struct ath_buf *bf,
		       struct ath_tx_status *ts, struct ath_txq *txq,
		       unsigned int flags)
{
	int qnum = txq->axq_qnum;

	TX_STAT_INC(sc, qnum, tx_pkts_all);
	sc->debug.stats.txstats[qnum].tx_bytes_all += bf->bf_mpdu->len;

	if (bf_isampdu(bf)) {
		if (flags & ATH_TX_ERROR)
			TX_STAT_INC(sc, qnum, a_xretries);
		else
			TX_STAT_INC(sc, qnum, a_completed);
	} else {
		if (ts->ts_status & ATH9K_TXERR_XRETRY)
			TX_STAT_INC(sc, qnum, xretries);
		else
			TX_STAT_INC(sc, qnum, completed);
	}

	if (ts->ts_status & ATH9K_TXERR_FILT)
		TX_STAT_INC(sc, qnum, txerr_filtered);
	if (ts->ts_status & ATH9K_TXERR_FIFO)
		TX_STAT_INC(sc, qnum, fifo_underrun);
	if (ts->ts_status & ATH9K_TXERR_XTXOP)
		TX_STAT_INC(sc, qnum, xtxop);
	if (ts->ts_status & ATH9K_TXERR_TIMER_EXPIRED)
		TX_STAT_INC(sc, qnum, timer_exp);
	if (ts->ts_flags & ATH9K_TX_DESC_CFG_ERR)
		TX_STAT_INC(sc, qnum, desc_cfg_err);
	if (ts->ts_flags & ATH9K_TX_DATA_UNDERRUN)
		TX_STAT_INC(sc, qnum, data_underrun);
	if (ts->ts_flags & ATH9K_TX_DELIM_UNDERRUN)
		TX_STAT_INC(sc, qnum, delim_underrun);
}