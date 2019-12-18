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
struct seq_file {int /*<<< orphan*/  private; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_aggr ; 
 int /*<<< orphan*/  a_completed ; 
 int /*<<< orphan*/  a_queued_hw ; 
 int /*<<< orphan*/  a_retries ; 
 int /*<<< orphan*/  a_xretries ; 
 int /*<<< orphan*/  completed ; 
 int /*<<< orphan*/  data_underrun ; 
 int /*<<< orphan*/  delim_underrun ; 
 int /*<<< orphan*/  desc_cfg_err ; 
 struct ieee80211_hw* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_underrun ; 
 int /*<<< orphan*/  puttxbuf ; 
 int /*<<< orphan*/  queued ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  timer_exp ; 
 int /*<<< orphan*/  tx_bytes_all ; 
 int /*<<< orphan*/  tx_pkts_all ; 
 int /*<<< orphan*/  txerr_filtered ; 
 int /*<<< orphan*/  txfailed ; 
 int /*<<< orphan*/  txprocdesc ; 
 int /*<<< orphan*/  txstart ; 
 int /*<<< orphan*/  xretries ; 
 int /*<<< orphan*/  xtxop ; 

__attribute__((used)) static int read_file_xmit(struct seq_file *file, void *data)
{
	struct ieee80211_hw *hw = dev_get_drvdata(file->private);
	struct ath_softc *sc = hw->priv;

	seq_printf(file, "%30s %10s%10s%10s\n\n", "BE", "BK", "VI", "VO");

	PR("MPDUs Queued:    ", queued);
	PR("MPDUs Completed: ", completed);
	PR("MPDUs XRetried:  ", xretries);
	PR("Aggregates:      ", a_aggr);
	PR("AMPDUs Queued HW:", a_queued_hw);
	PR("AMPDUs Completed:", a_completed);
	PR("AMPDUs Retried:  ", a_retries);
	PR("AMPDUs XRetried: ", a_xretries);
	PR("TXERR Filtered:  ", txerr_filtered);
	PR("FIFO Underrun:   ", fifo_underrun);
	PR("TXOP Exceeded:   ", xtxop);
	PR("TXTIMER Expiry:  ", timer_exp);
	PR("DESC CFG Error:  ", desc_cfg_err);
	PR("DATA Underrun:   ", data_underrun);
	PR("DELIM Underrun:  ", delim_underrun);
	PR("TX-Pkts-All:     ", tx_pkts_all);
	PR("TX-Bytes-All:    ", tx_bytes_all);
	PR("HW-put-tx-buf:   ", puttxbuf);
	PR("HW-tx-start:     ", txstart);
	PR("HW-tx-proc-desc: ", txprocdesc);
	PR("TX-Failed:       ", txfailed);

	return 0;
}