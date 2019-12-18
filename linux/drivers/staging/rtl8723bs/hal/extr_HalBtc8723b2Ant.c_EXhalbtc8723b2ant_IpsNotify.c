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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int bUnderIps; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 scalar_t__ BTC_IPS_ENTER ; 
 scalar_t__ BTC_IPS_LEAVE ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexAllOff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_IgnoreWlanAct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_InitCoexDm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_InitHwConfig (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_QueryBtInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_WifiOffHwCfg (int /*<<< orphan*/ ) ; 
 TYPE_1__* pCoexSta ; 

void EXhalbtc8723b2ant_IpsNotify(PBTC_COEXIST pBtCoexist, u8 type)
{
	if (BTC_IPS_ENTER == type) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS ENTER notify\n"));
		pCoexSta->bUnderIps = true;
		halbtc8723b2ant_WifiOffHwCfg(pBtCoexist);
		halbtc8723b2ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, true);
		halbtc8723b2ant_CoexAllOff(pBtCoexist);
	} else if (BTC_IPS_LEAVE == type) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS LEAVE notify\n"));
		pCoexSta->bUnderIps = false;
		halbtc8723b2ant_InitHwConfig(pBtCoexist, false);
		halbtc8723b2ant_InitCoexDm(pBtCoexist);
		halbtc8723b2ant_QueryBtInfo(pBtCoexist);
	}
}