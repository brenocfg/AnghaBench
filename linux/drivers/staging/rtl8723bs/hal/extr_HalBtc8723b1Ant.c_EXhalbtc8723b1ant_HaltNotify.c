#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bStopCoexDm; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_BT ; 
 int /*<<< orphan*/  BTC_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 int /*<<< orphan*/  EXhalbtc8723b1ant_MediaStatusNotify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  halbtc8723b1ant_IgnoreWlanAct (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PowerSaveState (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SetAntPath (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

void EXhalbtc8723b1ant_HaltNotify(PBTC_COEXIST pBtCoexist)
{
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Halt notify\n"));

	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 0);
	halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, false, true);

	halbtc8723b1ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, true);

	EXhalbtc8723b1ant_MediaStatusNotify(pBtCoexist, BTC_MEDIA_DISCONNECT);

	pBtCoexist->bStopCoexDm = true;
}