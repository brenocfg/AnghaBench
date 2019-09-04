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
typedef  int /*<<< orphan*/  work_func_t ;
struct qlcnic_adapter {int /*<<< orphan*/  fw_work; int /*<<< orphan*/  qlcnic_wq; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_AER ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_schedule_work(struct qlcnic_adapter *adapter,
			  work_func_t func, int delay)
{
	if (test_bit(__QLCNIC_AER, &adapter->state))
		return;

	INIT_DELAYED_WORK(&adapter->fw_work, func);
	queue_delayed_work(adapter->qlcnic_wq, &adapter->fw_work,
			   round_jiffies_relative(delay));
}