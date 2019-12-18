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
struct TYPE_3__ {int /*<<< orphan*/  func; } ;
struct TYPE_4__ {TYPE_1__ work; } ;
struct qlcnic_adapter {TYPE_2__ fw_work; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (TYPE_2__*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void qlcnic_82xx_cancel_idc_work(struct qlcnic_adapter *adapter)
{
	while (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		usleep_range(10000, 11000);

	if (!adapter->fw_work.work.func)
		return;

	cancel_delayed_work_sync(&adapter->fw_work);
}