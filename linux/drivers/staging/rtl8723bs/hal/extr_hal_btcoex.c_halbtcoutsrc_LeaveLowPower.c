#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {struct adapter* Adapter; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTCOEX_ALIVE ; 
 unsigned long LPS_RPWM_WAIT_MS ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 unsigned long jiffies ; 
 unsigned long jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ rtw_register_task_alive (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtcoutsrc_LeaveLowPower(PBTC_COEXIST pBtCoexist)
{
	struct adapter *padapter;
	s32 ready;
	unsigned long stime;
	unsigned long utime;
	u32 timeout; /*  unit: ms */


	padapter = pBtCoexist->Adapter;
	ready = _FAIL;
#ifdef LPS_RPWM_WAIT_MS
	timeout = LPS_RPWM_WAIT_MS;
#else /*  !LPS_RPWM_WAIT_MS */
	timeout = 30;
#endif /*  !LPS_RPWM_WAIT_MS */

	stime = jiffies;
	do {
		ready = rtw_register_task_alive(padapter, BTCOEX_ALIVE);
		if (_SUCCESS == ready)
			break;

		utime = jiffies_to_msecs(jiffies - stime);
		if (utime > timeout)
			break;

		msleep(1);
	} while (1);
}