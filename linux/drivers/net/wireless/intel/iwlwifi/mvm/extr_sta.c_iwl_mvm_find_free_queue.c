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
typedef  int u8 ;
struct iwl_mvm {TYPE_1__* queue_info; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {scalar_t__ tid_bitmap; scalar_t__ status; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IWL_MVM_QUEUE_FREE ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_find_free_queue(struct iwl_mvm *mvm, u8 sta_id,
				   u8 minq, u8 maxq)
{
	int i;

	lockdep_assert_held(&mvm->mutex);

	/* This should not be hit with new TX path */
	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return -ENOSPC;

	/* Start by looking for a free queue */
	for (i = minq; i <= maxq; i++)
		if (mvm->queue_info[i].tid_bitmap == 0 &&
		    mvm->queue_info[i].status == IWL_MVM_QUEUE_FREE)
			return i;

	return -ENOSPC;
}