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
struct netxen_adapter {int /*<<< orphan*/  fw_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
netxen_schedule_work(struct netxen_adapter *adapter,
		work_func_t func, int delay)
{
	INIT_DELAYED_WORK(&adapter->fw_work, func);
	schedule_delayed_work(&adapter->fw_work, delay);
}