#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_10__ {int bStopCoexDm; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_BT ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BTC_PS_WIFI_NATIVE ; 
 scalar_t__ BTC_WIFI_PNP_SLEEP ; 
 scalar_t__ BTC_WIFI_PNP_WAKE_UP ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_InitCoexDm (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_InitHwConfig (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PowerSaveState (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_QueryBtInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SetAntPath (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

void EXhalbtc8723b1ant_PnpNotify(PBTC_COEXIST pBtCoexist, u8 pnpState)
{
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify\n"));

	if (BTC_WIFI_PNP_SLEEP == pnpState) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify to SLEEP\n"));

		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, false, true);

		pBtCoexist->bStopCoexDm = true;
	} else if (BTC_WIFI_PNP_WAKE_UP == pnpState) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify to WAKE UP\n"));
		pBtCoexist->bStopCoexDm = false;
		halbtc8723b1ant_InitHwConfig(pBtCoexist, false, false);
		halbtc8723b1ant_InitCoexDm(pBtCoexist);
		halbtc8723b1ant_QueryBtInfo(pBtCoexist);
	}
}