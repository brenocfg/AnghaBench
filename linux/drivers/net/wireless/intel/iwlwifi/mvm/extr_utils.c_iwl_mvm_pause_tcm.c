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
struct TYPE_2__ {int paused; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct iwl_mvm {TYPE_1__ tcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_mvm_pause_tcm(struct iwl_mvm *mvm, bool with_cancel)
{
	spin_lock_bh(&mvm->tcm.lock);
	mvm->tcm.paused = true;
	spin_unlock_bh(&mvm->tcm.lock);
	if (with_cancel)
		cancel_delayed_work_sync(&mvm->tcm.work);
}