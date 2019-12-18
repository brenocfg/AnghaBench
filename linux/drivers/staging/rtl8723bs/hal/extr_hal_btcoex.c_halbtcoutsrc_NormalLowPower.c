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
struct adapter {int dummy; } ;
struct TYPE_3__ {struct adapter* Adapter; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTCOEX_ALIVE ; 
 int /*<<< orphan*/  rtw_unregister_task_alive (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtcoutsrc_NormalLowPower(PBTC_COEXIST pBtCoexist)
{
	struct adapter *padapter;


	padapter = pBtCoexist->Adapter;
	rtw_unregister_task_alive(padapter, BTCOEX_ALIVE);
}