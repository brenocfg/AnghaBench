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
struct iwl_mvm {int beacon_inject_active; TYPE_1__* hw; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {scalar_t__ extra_beacon_tailroom; } ;

/* Variables and functions */
 int _iwl_dbgfs_inject_beacon_ie (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_inject_beacon_ie_restore_write(struct iwl_mvm *mvm,
							char *buf,
							size_t count,
							loff_t *ppos)
{
	int ret = _iwl_dbgfs_inject_beacon_ie(mvm, NULL, 0);

	mvm->hw->extra_beacon_tailroom = 0;
	mvm->beacon_inject_active = false;
	return ret ?: count;
}