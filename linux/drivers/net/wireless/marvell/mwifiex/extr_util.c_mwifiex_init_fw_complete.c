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
struct TYPE_2__ {int /*<<< orphan*/  (* init_fw_port ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {scalar_t__ hw_status; int init_wait_q_woken; int /*<<< orphan*/  init_wait_q; TYPE_1__ if_ops; } ;

/* Variables and functions */
 scalar_t__ MWIFIEX_HW_STATUS_READY ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int mwifiex_init_fw_complete(struct mwifiex_adapter *adapter)
{

	if (adapter->hw_status == MWIFIEX_HW_STATUS_READY)
		if (adapter->if_ops.init_fw_port)
			adapter->if_ops.init_fw_port(adapter);

	adapter->init_wait_q_woken = true;
	wake_up_interruptible(&adapter->init_wait_q);
	return 0;
}