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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int ps_disabled; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_get_systime (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_power_update_device (struct iwl_mvm*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_mvm_get_sync_time(struct iwl_mvm *mvm, u32 *gp2, u64 *boottime)
{
	bool ps_disabled;

	lockdep_assert_held(&mvm->mutex);

	/* Disable power save when reading GP2 */
	ps_disabled = mvm->ps_disabled;
	if (!ps_disabled) {
		mvm->ps_disabled = true;
		iwl_mvm_power_update_device(mvm);
	}

	*gp2 = iwl_mvm_get_systime(mvm);
	*boottime = ktime_get_boottime_ns();

	if (!ps_disabled) {
		mvm->ps_disabled = ps_disabled;
		iwl_mvm_power_update_device(mvm);
	}
}