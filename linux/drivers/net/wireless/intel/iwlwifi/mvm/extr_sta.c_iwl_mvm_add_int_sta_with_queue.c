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
typedef  int u16 ;
struct iwl_mvm_int_sta {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MAX_TID_COUNT ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,struct iwl_mvm_int_sta*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_disable_txq (struct iwl_mvm*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_enable_aux_snif_queue (struct iwl_mvm*,int,int /*<<< orphan*/ ,int) ; 
 int iwl_mvm_enable_aux_snif_queue_tvqm (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_rm_sta_common (struct iwl_mvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_add_int_sta_with_queue(struct iwl_mvm *mvm, int macidx,
					  int maccolor,
					  struct iwl_mvm_int_sta *sta,
					  u16 *queue, int fifo)
{
	int ret;

	/* Map queue to fifo - needs to happen before adding station */
	if (!iwl_mvm_has_new_tx_api(mvm))
		iwl_mvm_enable_aux_snif_queue(mvm, *queue, sta->sta_id, fifo);

	ret = iwl_mvm_add_int_sta_common(mvm, sta, NULL, macidx, maccolor);
	if (ret) {
		if (!iwl_mvm_has_new_tx_api(mvm))
			iwl_mvm_disable_txq(mvm, NULL, *queue,
					    IWL_MAX_TID_COUNT, 0);
		return ret;
	}

	/*
	 * For 22000 firmware and on we cannot add queue to a station unknown
	 * to firmware so enable queue here - after the station was added
	 */
	if (iwl_mvm_has_new_tx_api(mvm)) {
		int txq;

		txq = iwl_mvm_enable_aux_snif_queue_tvqm(mvm, sta->sta_id);
		if (txq < 0) {
			iwl_mvm_rm_sta_common(mvm, sta->sta_id);
			return txq;
		}

		*queue = txq;
	}

	return 0;
}