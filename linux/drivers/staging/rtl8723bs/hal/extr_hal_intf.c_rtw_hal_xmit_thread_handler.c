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
struct TYPE_2__ {int /*<<< orphan*/  (* xmit_thread_handler ) (struct adapter*) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  stub1 (struct adapter*) ; 

s32 rtw_hal_xmit_thread_handler(struct adapter *padapter)
{
	if (padapter->HalFunc.xmit_thread_handler)
		return padapter->HalFunc.xmit_thread_handler(padapter);
	return _FAIL;
}