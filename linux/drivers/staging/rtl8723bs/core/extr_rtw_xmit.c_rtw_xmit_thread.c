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
struct TYPE_2__ {int /*<<< orphan*/  terminate_xmitthread_comp; } ;
struct adapter {TYPE_1__ xmitpriv; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_signals_thread () ; 
 scalar_t__ rtw_hal_xmit_thread_handler (struct adapter*) ; 
 int /*<<< orphan*/  thread_enter (char*) ; 
 int /*<<< orphan*/  thread_exit () ; 

int rtw_xmit_thread(void *context)
{
	s32 err;
	struct adapter *padapter;


	err = _SUCCESS;
	padapter = context;

	thread_enter("RTW_XMIT_THREAD");

	do {
		err = rtw_hal_xmit_thread_handler(padapter);
		flush_signals_thread();
	} while (_SUCCESS == err);

	complete(&padapter->xmitpriv.terminate_xmitthread_comp);

	thread_exit();
}