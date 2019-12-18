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
struct TYPE_2__ {int /*<<< orphan*/  terminate_cmdthread_comp; } ;
struct adapter {TYPE_1__ cmdpriv; int /*<<< orphan*/  cmdThread; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct adapter*,char*) ; 
 int /*<<< orphan*/  rtw_cmd_thread ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtw_start_drv_threads(struct adapter *padapter)
{
	int err = 0;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+rtw_start_drv_threads\n"));

	padapter->cmdThread = kthread_run(rtw_cmd_thread, padapter,
					  "RTW_CMD_THREAD");
	if (IS_ERR(padapter->cmdThread))
		err = PTR_ERR(padapter->cmdThread);
	else
		/* wait for cmd_thread to run */
		wait_for_completion_interruptible(&padapter->cmdpriv.terminate_cmdthread_comp);

	return err;
}