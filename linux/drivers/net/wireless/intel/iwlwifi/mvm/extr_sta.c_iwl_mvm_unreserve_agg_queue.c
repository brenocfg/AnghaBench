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
typedef  size_t u16 ;
struct iwl_mvm_tid_data {size_t txq_id; } ;
struct iwl_mvm_sta {int dummy; } ;
struct iwl_mvm {TYPE_1__* queue_info; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 size_t IWL_MVM_INVALID_QUEUE ; 
 scalar_t__ IWL_MVM_QUEUE_FREE ; 
 scalar_t__ IWL_MVM_QUEUE_RESERVED ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_unreserve_agg_queue(struct iwl_mvm *mvm,
					struct iwl_mvm_sta *mvmsta,
					struct iwl_mvm_tid_data *tid_data)
{
	u16 txq_id = tid_data->txq_id;

	lockdep_assert_held(&mvm->mutex);

	if (iwl_mvm_has_new_tx_api(mvm))
		return;

	/*
	 * The TXQ is marked as reserved only if no traffic came through yet
	 * This means no traffic has been sent on this TID (agg'd or not), so
	 * we no longer have use for the queue. Since it hasn't even been
	 * allocated through iwl_mvm_enable_txq, so we can just mark it back as
	 * free.
	 */
	if (mvm->queue_info[txq_id].status == IWL_MVM_QUEUE_RESERVED) {
		mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_FREE;
		tid_data->txq_id = IWL_MVM_INVALID_QUEUE;
	}
}