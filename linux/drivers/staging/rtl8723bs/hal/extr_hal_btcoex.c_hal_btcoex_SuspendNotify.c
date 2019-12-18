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
typedef  int u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BTC_WIFI_PNP_SLEEP ; 
 int BTC_WIFI_PNP_WAKE_UP ; 
 int /*<<< orphan*/  EXhalbtcoutsrc_PnpNotify (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GLBtCoexist ; 

void hal_btcoex_SuspendNotify(struct adapter *padapter, u8 state)
{
	if (state == 1)
		state = BTC_WIFI_PNP_SLEEP;
	else
		state = BTC_WIFI_PNP_WAKE_UP;

	EXhalbtcoutsrc_PnpNotify(&GLBtCoexist, state);
}