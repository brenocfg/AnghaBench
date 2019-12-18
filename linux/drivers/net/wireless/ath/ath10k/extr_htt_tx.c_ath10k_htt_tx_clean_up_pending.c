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
struct htt_tx_done {int msdu_id; int /*<<< orphan*/  status; int /*<<< orphan*/  member_0; } ;
struct ath10k_htt {int dummy; } ;
struct ath10k {struct ath10k_htt htt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  HTT_TX_COMPL_STATE_DISCARD ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath10k_txrx_tx_unref (struct ath10k_htt*,struct htt_tx_done*) ; 

__attribute__((used)) static int ath10k_htt_tx_clean_up_pending(int msdu_id, void *skb, void *ctx)
{
	struct ath10k *ar = ctx;
	struct ath10k_htt *htt = &ar->htt;
	struct htt_tx_done tx_done = {0};

	ath10k_dbg(ar, ATH10K_DBG_HTT, "force cleanup msdu_id %hu\n", msdu_id);

	tx_done.msdu_id = msdu_id;
	tx_done.status = HTT_TX_COMPL_STATE_DISCARD;

	ath10k_txrx_tx_unref(htt, &tx_done);

	return 0;
}