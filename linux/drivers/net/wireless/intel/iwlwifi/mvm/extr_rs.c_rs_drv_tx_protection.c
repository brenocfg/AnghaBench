#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_lq_cmd {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {struct iwl_lq_cmd lq; } ;
struct TYPE_4__ {TYPE_1__ rs_drv; } ;
struct iwl_mvm_sta {scalar_t__ tx_protection; TYPE_2__ lq_sta; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  LQ_FLAG_USE_RTS_MSK ; 
 int iwl_mvm_send_lq_cmd (struct iwl_mvm*,struct iwl_lq_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rs_drv_tx_protection(struct iwl_mvm *mvm, struct iwl_mvm_sta *mvmsta,
				bool enable)
{
	struct iwl_lq_cmd *lq = &mvmsta->lq_sta.rs_drv.lq;

	lockdep_assert_held(&mvm->mutex);

	if (enable) {
		if (mvmsta->tx_protection == 0)
			lq->flags |= LQ_FLAG_USE_RTS_MSK;
		mvmsta->tx_protection++;
	} else {
		mvmsta->tx_protection--;
		if (mvmsta->tx_protection == 0)
			lq->flags &= ~LQ_FLAG_USE_RTS_MSK;
	}

	return iwl_mvm_send_lq_cmd(mvm, lq);
}