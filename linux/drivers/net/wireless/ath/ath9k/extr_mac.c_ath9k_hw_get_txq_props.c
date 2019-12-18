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
struct ath_hw {struct ath9k_tx_queue_info* txq; } ;
struct ath_common {int dummy; } ;
struct ath9k_tx_queue_info {scalar_t__ tqi_type; int /*<<< orphan*/  tqi_readyTime; int /*<<< orphan*/  tqi_burstTime; int /*<<< orphan*/  tqi_cbrOverflowLimit; int /*<<< orphan*/  tqi_cbrPeriod; int /*<<< orphan*/  tqi_lgretry; int /*<<< orphan*/  tqi_shretry; int /*<<< orphan*/  tqi_cwmax; int /*<<< orphan*/  tqi_cwmin; int /*<<< orphan*/  tqi_aifs; int /*<<< orphan*/  tqi_priority; int /*<<< orphan*/  tqi_qflags; int /*<<< orphan*/  tqi_subtype; int /*<<< orphan*/  tqi_ver; } ;

/* Variables and functions */
 scalar_t__ ATH9K_TX_QUEUE_INACTIVE ; 
 int /*<<< orphan*/  QUEUE ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

bool ath9k_hw_get_txq_props(struct ath_hw *ah, int q,
			    struct ath9k_tx_queue_info *qinfo)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_tx_queue_info *qi;

	qi = &ah->txq[q];
	if (qi->tqi_type == ATH9K_TX_QUEUE_INACTIVE) {
		ath_dbg(common, QUEUE,
			"Get TXQ properties, inactive queue: %u\n", q);
		return false;
	}

	qinfo->tqi_qflags = qi->tqi_qflags;
	qinfo->tqi_ver = qi->tqi_ver;
	qinfo->tqi_subtype = qi->tqi_subtype;
	qinfo->tqi_qflags = qi->tqi_qflags;
	qinfo->tqi_priority = qi->tqi_priority;
	qinfo->tqi_aifs = qi->tqi_aifs;
	qinfo->tqi_cwmin = qi->tqi_cwmin;
	qinfo->tqi_cwmax = qi->tqi_cwmax;
	qinfo->tqi_shretry = qi->tqi_shretry;
	qinfo->tqi_lgretry = qi->tqi_lgretry;
	qinfo->tqi_cbrPeriod = qi->tqi_cbrPeriod;
	qinfo->tqi_cbrOverflowLimit = qi->tqi_cbrOverflowLimit;
	qinfo->tqi_burstTime = qi->tqi_burstTime;
	qinfo->tqi_readyTime = qi->tqi_readyTime;

	return true;
}