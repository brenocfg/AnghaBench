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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  terminate_cmdthread_comp; } ;
struct adapter {TYPE_1__ cmdpriv; void* cmdThread; void* xmitThread; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 void* kthread_run (int /*<<< orphan*/ ,struct adapter*,char*) ; 
 int /*<<< orphan*/  rtw_cmd_thread ; 
 int /*<<< orphan*/  rtw_hal_start_thread (struct adapter*) ; 
 int /*<<< orphan*/  rtw_xmit_thread ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

u32 rtw_start_drv_threads(struct adapter *padapter)
{
	u32 _status = _SUCCESS;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+rtw_start_drv_threads\n"));
	padapter->xmitThread = kthread_run(rtw_xmit_thread, padapter, "RTW_XMIT_THREAD");
	if (IS_ERR(padapter->xmitThread))
		_status = _FAIL;

	padapter->cmdThread = kthread_run(rtw_cmd_thread, padapter, "RTW_CMD_THREAD");
	if (IS_ERR(padapter->cmdThread))
		_status = _FAIL;
	else
		wait_for_completion(&padapter->cmdpriv.terminate_cmdthread_comp); /* wait for cmd_thread to run */

	rtw_hal_start_thread(padapter);
	return _status;
}