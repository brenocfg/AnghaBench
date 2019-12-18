#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_12__ {int curArfrType; int preArfrType; int backupArfrCnt1; int backupArfrCnt2; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* fBtcWrite4Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_B_MODE ; 
 TYPE_9__* pCoexDm ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int,int) ; 

__attribute__((used)) static void halbtc8723b1ant_AutoRateFallbackRetry(
	PBTC_COEXIST pBtCoexist, bool bForceExec, u8 type
)
{
	bool bWifiUnderBMode = false;

	pCoexDm->curArfrType = type;

	if (bForceExec || (pCoexDm->preArfrType != pCoexDm->curArfrType)) {
		switch (pCoexDm->curArfrType) {
		case 0:	/*  normal mode */
			pBtCoexist->fBtcWrite4Byte(
				pBtCoexist, 0x430, pCoexDm->backupArfrCnt1
			);
			pBtCoexist->fBtcWrite4Byte(
				pBtCoexist, 0x434, pCoexDm->backupArfrCnt2
			);
			break;
		case 1:
			pBtCoexist->fBtcGet(
				pBtCoexist, BTC_GET_BL_WIFI_UNDER_B_MODE, &bWifiUnderBMode
			);
			if (bWifiUnderBMode) {
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x430, 0x0);
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x434, 0x01010101);
			} else {
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x430, 0x0);
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x434, 0x04030201);
			}
			break;
		default:
			break;
		}
	}

	pCoexDm->preArfrType = pCoexDm->curArfrType;
}