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
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct mwifiex_adapter {int /*<<< orphan*/  hs_activate_wait_q; TYPE_1__ cmd_wait_q; int /*<<< orphan*/  devdump_timer; int /*<<< orphan*/  wakeup_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_cancel_all_pending_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwifiex_adapter_cleanup(struct mwifiex_adapter *adapter)
{
	del_timer(&adapter->wakeup_timer);
	del_timer_sync(&adapter->devdump_timer);
	mwifiex_cancel_all_pending_cmd(adapter);
	wake_up_interruptible(&adapter->cmd_wait_q.wait);
	wake_up_interruptible(&adapter->hs_activate_wait_q);
}