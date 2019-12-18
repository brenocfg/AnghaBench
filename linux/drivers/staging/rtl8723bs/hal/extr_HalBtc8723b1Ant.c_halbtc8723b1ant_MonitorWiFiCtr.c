#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int s32 ;
struct TYPE_20__ {scalar_t__ (* fBtcRead4Byte ) (TYPE_1__*,int) ;scalar_t__ (* fBtcRead2Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcWrite1ByteBitMask ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_19__ {scalar_t__ btStatus; } ;
struct TYPE_18__ {scalar_t__ nCRCOK_CCK; scalar_t__ nCRCOK_11g; scalar_t__ nCRCOK_11n; scalar_t__ nCRCOK_11nAgg; scalar_t__ nCRCErr_CCK; scalar_t__ nCRCErr_11g; scalar_t__ nCRCErr_11n; scalar_t__ nCRCErr_11nAgg; int bPreCCKLock; int bCCKLock; scalar_t__ bUnderIps; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_BL_WIFI_BUSY ; 
 int /*<<< orphan*/  BTC_GET_BL_WIFI_UNDER_B_MODE ; 
 int /*<<< orphan*/  BTC_GET_S4_WIFI_RSSI ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY ; 
 scalar_t__ BT_8723B_1ANT_BT_STATUS_SCO_BUSY ; 
 TYPE_16__* pCoexDm ; 
 TYPE_15__* pCoexSta ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub10 (TYPE_1__*,int) ; 
 scalar_t__ stub11 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub13 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (TYPE_1__*,int) ; 
 scalar_t__ stub5 (TYPE_1__*,int) ; 
 scalar_t__ stub6 (TYPE_1__*,int) ; 
 scalar_t__ stub7 (TYPE_1__*,int) ; 
 scalar_t__ stub8 (TYPE_1__*,int) ; 
 scalar_t__ stub9 (TYPE_1__*,int) ; 

__attribute__((used)) static void halbtc8723b1ant_MonitorWiFiCtr(PBTC_COEXIST pBtCoexist)
{
	s32	wifiRssi = 0;
	bool bWifiBusy = false, bWifiUnderBMode = false;
	static u8 nCCKLockCounter;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWifiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_WIFI_RSSI, &wifiRssi);
	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_UNDER_B_MODE, &bWifiUnderBMode
	);

	if (pCoexSta->bUnderIps) {
		pCoexSta->nCRCOK_CCK = 0;
		pCoexSta->nCRCOK_11g = 0;
		pCoexSta->nCRCOK_11n = 0;
		pCoexSta->nCRCOK_11nAgg = 0;

		pCoexSta->nCRCErr_CCK = 0;
		pCoexSta->nCRCErr_11g = 0;
		pCoexSta->nCRCErr_11n = 0;
		pCoexSta->nCRCErr_11nAgg = 0;
	} else {
		pCoexSta->nCRCOK_CCK	= pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xf88);
		pCoexSta->nCRCOK_11g	= pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf94);
		pCoexSta->nCRCOK_11n	= pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf90);
		pCoexSta->nCRCOK_11nAgg = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xfb8);

		pCoexSta->nCRCErr_CCK	 = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xf84);
		pCoexSta->nCRCErr_11g	 = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf96);
		pCoexSta->nCRCErr_11n	 = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf92);
		pCoexSta->nCRCErr_11nAgg = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xfba);
	}


	/* reset counter */
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0xf16, 0x1, 0x1);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0xf16, 0x1, 0x0);

	if (bWifiBusy && (wifiRssi >= 30) && !bWifiUnderBMode) {
		if (
			(pCoexDm->btStatus == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) ||
			(pCoexDm->btStatus == BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) ||
			(pCoexDm->btStatus == BT_8723B_1ANT_BT_STATUS_SCO_BUSY)
		) {
			if (
				pCoexSta->nCRCOK_CCK > (
					pCoexSta->nCRCOK_11g +
					pCoexSta->nCRCOK_11n +
					pCoexSta->nCRCOK_11nAgg
				)
			) {
				if (nCCKLockCounter < 5)
				 nCCKLockCounter++;
			} else {
				if (nCCKLockCounter > 0)
				 nCCKLockCounter--;
			}

		} else {
			if (nCCKLockCounter > 0)
			  nCCKLockCounter--;
		}
	} else {
		if (nCCKLockCounter > 0)
			nCCKLockCounter--;
	}

	if (!pCoexSta->bPreCCKLock) {

		if (nCCKLockCounter >= 5)
		 pCoexSta->bCCKLock = true;
		else
		 pCoexSta->bCCKLock = false;
	} else {
		if (nCCKLockCounter == 0)
		 pCoexSta->bCCKLock = false;
		else
		 pCoexSta->bCCKLock = true;
	}

	pCoexSta->bPreCCKLock =  pCoexSta->bCCKLock;


}