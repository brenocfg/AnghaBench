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
struct rtllib_device {int bTxEnableFwCalcDur; scalar_t__ bTxUseDriverAssingedRate; scalar_t__ bTxDisableRateFallBack; struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {int bAcceptAddbaReq; int bRegShortGI20MHz; int bRegShortGI40MHz; int bRegBW40MHz; int bRegSuppCCK; unsigned long nAMSDU_MaxSize; int bAMPDUEnable; int AMPDU_Factor; int SelfMimoPs; int bRegRT2RTAggregation; int bRegRxReorderEnable; int RxReorderWinSize; int RxReorderPendingTime; scalar_t__ MPDU_Density; scalar_t__ bAMSDU_Support; } ;

/* Variables and functions */

void HTUpdateDefaultSetting(struct rtllib_device *ieee)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	pHTInfo->bAcceptAddbaReq = 1;

	pHTInfo->bRegShortGI20MHz = 1;
	pHTInfo->bRegShortGI40MHz = 1;

	pHTInfo->bRegBW40MHz = 1;

	if (pHTInfo->bRegBW40MHz)
		pHTInfo->bRegSuppCCK = 1;
	else
		pHTInfo->bRegSuppCCK = true;

	pHTInfo->nAMSDU_MaxSize = 7935UL;
	pHTInfo->bAMSDU_Support = 0;

	pHTInfo->bAMPDUEnable = 1;
	pHTInfo->AMPDU_Factor = 2;
	pHTInfo->MPDU_Density = 0;

	pHTInfo->SelfMimoPs = 3;
	if (pHTInfo->SelfMimoPs == 2)
		pHTInfo->SelfMimoPs = 3;
	ieee->bTxDisableRateFallBack = 0;
	ieee->bTxUseDriverAssingedRate = 0;

	ieee->bTxEnableFwCalcDur = 1;

	pHTInfo->bRegRT2RTAggregation = 1;

	pHTInfo->bRegRxReorderEnable = 1;
	pHTInfo->RxReorderWinSize = 64;
	pHTInfo->RxReorderPendingTime = 30;
}