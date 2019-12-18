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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* card_reset ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {TYPE_1__ if_ops; int /*<<< orphan*/  hw_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MWIFIEX_HW_STATUS_RESET ; 
 struct mwifiex_adapter* adapter ; 
 struct mwifiex_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_cancel_all_pending_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  wakeup_timer ; 

__attribute__((used)) static void wakeup_timer_fn(struct timer_list *t)
{
	struct mwifiex_adapter *adapter = from_timer(adapter, t, wakeup_timer);

	mwifiex_dbg(adapter, ERROR, "Firmware wakeup failed\n");
	adapter->hw_status = MWIFIEX_HW_STATUS_RESET;
	mwifiex_cancel_all_pending_cmd(adapter);

	if (adapter->if_ops.card_reset)
		adapter->if_ops.card_reset(adapter);
}