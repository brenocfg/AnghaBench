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
struct TYPE_2__ {int stop_req; int /*<<< orphan*/  terminate_cmdthread_comp; int /*<<< orphan*/  cmd_queue_comp; int /*<<< orphan*/  cmdthd_running; } ;
struct adapter {TYPE_1__ cmdpriv; scalar_t__ cmdThread; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void rtw_stop_cmd_thread(struct adapter *adapter)
{
	if (adapter->cmdThread &&
		atomic_read(&(adapter->cmdpriv.cmdthd_running)) == true &&
		adapter->cmdpriv.stop_req == 0) {
		adapter->cmdpriv.stop_req = 1;
		complete(&adapter->cmdpriv.cmd_queue_comp);
		wait_for_completion(&adapter->cmdpriv.terminate_cmdthread_comp);
	}
}