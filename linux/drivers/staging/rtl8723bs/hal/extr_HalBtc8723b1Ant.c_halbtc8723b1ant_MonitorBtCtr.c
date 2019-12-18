#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {int highPriorityTx; int highPriorityRx; int lowPriorityTx; int lowPriorityRx; int /*<<< orphan*/  popEventCnt; int /*<<< orphan*/  bC2hBtInquiryPage; scalar_t__ bUnderIps; } ;
struct TYPE_8__ {int (* fBtcRead4Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int bMaskHWord ; 
 int bMaskLWord ; 
 int /*<<< orphan*/  halbtc8723b1ant_QueryBtInfo (TYPE_1__*) ; 
 TYPE_5__* pCoexSta ; 
 int stub1 (TYPE_1__*,int) ; 
 int stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int) ; 

__attribute__((used)) static void halbtc8723b1ant_MonitorBtCtr(PBTC_COEXIST pBtCoexist)
{
	u32 regHPTxRx, regLPTxRx, u4Tmp;
	u32 regHPTx = 0, regHPRx = 0, regLPTx = 0, regLPRx = 0;
	static u8 NumOfBtCounterChk;

       /* to avoid 0x76e[3] = 1 (WLAN_Act control by PTA) during IPS */
	/* if (! (pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x76e) & 0x8)) */

	if (pCoexSta->bUnderIps) {
		pCoexSta->highPriorityTx = 65535;
		pCoexSta->highPriorityRx = 65535;
		pCoexSta->lowPriorityTx = 65535;
		pCoexSta->lowPriorityRx = 65535;
		return;
	}

	regHPTxRx = 0x770;
	regLPTxRx = 0x774;

	u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, regHPTxRx);
	regHPTx = u4Tmp & bMaskLWord;
	regHPRx = (u4Tmp & bMaskHWord)>>16;

	u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, regLPTxRx);
	regLPTx = u4Tmp & bMaskLWord;
	regLPRx = (u4Tmp & bMaskHWord)>>16;

	pCoexSta->highPriorityTx = regHPTx;
	pCoexSta->highPriorityRx = regHPRx;
	pCoexSta->lowPriorityTx = regLPTx;
	pCoexSta->lowPriorityRx = regLPRx;

	if ((pCoexSta->lowPriorityTx >= 1050) && (!pCoexSta->bC2hBtInquiryPage))
		pCoexSta->popEventCnt++;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE,
		(
			"[BTCoex], Hi-Pri Rx/Tx: %d/%d, Lo-Pri Rx/Tx: %d/%d\n",
			regHPRx,
			regHPTx,
			regLPRx,
			regLPTx
		)
	);

	/*  reset counter */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc);

	if ((regHPTx == 0) && (regHPRx == 0) && (regLPTx == 0) && (regLPRx == 0)) {
		NumOfBtCounterChk++;
		if (NumOfBtCounterChk >= 3) {
			halbtc8723b1ant_QueryBtInfo(pBtCoexist);
			NumOfBtCounterChk = 0;
		}
	}
}