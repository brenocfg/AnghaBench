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
struct ath_hw {int dummy; } ;
struct ath9k_tx_queue_info {int tqi_cwmin; int /*<<< orphan*/  tqi_readyTime; int /*<<< orphan*/  tqi_burstTime; int /*<<< orphan*/  tqi_cwmax; int /*<<< orphan*/  tqi_aifs; } ;
struct ath9k_htc_priv {struct ath_hw* ah; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_get_txq_props (struct ath_hw*,int,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  ath9k_hw_resettxqueue (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_txq_props (struct ath_hw*,int,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*,int) ; 

int ath_htc_txq_update(struct ath9k_htc_priv *priv, int qnum,
		       struct ath9k_tx_queue_info *qinfo)
{
	struct ath_hw *ah = priv->ah;
	int error = 0;
	struct ath9k_tx_queue_info qi;

	ath9k_hw_get_txq_props(ah, qnum, &qi);

	qi.tqi_aifs = qinfo->tqi_aifs;
	qi.tqi_cwmin = qinfo->tqi_cwmin / 2; /* XXX */
	qi.tqi_cwmax = qinfo->tqi_cwmax;
	qi.tqi_burstTime = qinfo->tqi_burstTime;
	qi.tqi_readyTime = qinfo->tqi_readyTime;

	if (!ath9k_hw_set_txq_props(ah, qnum, &qi)) {
		ath_err(ath9k_hw_common(ah),
			"Unable to update hardware queue %u!\n", qnum);
		error = -EIO;
	} else {
		ath9k_hw_resettxqueue(ah, qnum);
	}

	return error;
}