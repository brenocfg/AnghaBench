#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_HS_OPERATION ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_4_WAY_PROGRESS ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_CONNECTED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool halbtc8723b1ant_IsWifiStatusChanged(PBTC_COEXIST pBtCoexist)
{
	static bool	bPreWifiBusy, bPreUnder4way, bPreBtHsOn;
	bool bWifiBusy = false, bUnder4way = false, bBtHsOn = false;
	bool bWifiConnected = false;

	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWifiConnected
	);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWifiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS, &bUnder4way
	);

	if (bWifiConnected) {
		if (bWifiBusy != bPreWifiBusy) {
			bPreWifiBusy = bWifiBusy;
			return true;
		}

		if (bUnder4way != bPreUnder4way) {
			bPreUnder4way = bUnder4way;
			return true;
		}

		if (bBtHsOn != bPreBtHsOn) {
			bPreBtHsOn = bBtHsOn;
			return true;
		}
	}

	return false;
}