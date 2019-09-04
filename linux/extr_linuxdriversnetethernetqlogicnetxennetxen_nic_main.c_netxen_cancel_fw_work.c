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
struct netxen_adapter {int /*<<< orphan*/  fw_work; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NX_RESETTING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
netxen_cancel_fw_work(struct netxen_adapter *adapter)
{
	while (test_and_set_bit(__NX_RESETTING, &adapter->state))
		msleep(10);

	cancel_delayed_work_sync(&adapter->fw_work);
}