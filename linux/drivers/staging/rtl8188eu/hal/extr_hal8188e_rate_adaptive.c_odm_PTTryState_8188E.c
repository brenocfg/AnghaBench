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
struct odm_ra_info {int PTTryState; int PTModeSS; int DecisionRate; int RssiStaRA; int PTStage; int PTStopCount; int PTPreRssi; scalar_t__ PTPreRate; scalar_t__ RAstage; } ;

/* Variables and functions */

__attribute__((used)) static void odm_PTTryState_8188E(struct odm_ra_info *pRaInfo)
{
	pRaInfo->PTTryState = 0;
	switch (pRaInfo->PTModeSS) {
	case 3:
		if (pRaInfo->DecisionRate >= 0x19)
			pRaInfo->PTTryState = 1;
		break;
	case 2:
		if (pRaInfo->DecisionRate >= 0x11)
			pRaInfo->PTTryState = 1;
		break;
	case 1:
		if (pRaInfo->DecisionRate >= 0x0a)
			pRaInfo->PTTryState = 1;
		break;
	case 0:
		if (pRaInfo->DecisionRate >= 0x03)
			pRaInfo->PTTryState = 1;
		break;
	default:
		pRaInfo->PTTryState = 0;
		break;
	}

	if (pRaInfo->RssiStaRA < 48) {
		pRaInfo->PTStage = 0;
	} else if (pRaInfo->PTTryState == 1) {
		if ((pRaInfo->PTStopCount >= 10) ||
		    (pRaInfo->PTPreRssi > pRaInfo->RssiStaRA + 5) ||
		    (pRaInfo->PTPreRssi < pRaInfo->RssiStaRA - 5) ||
		    (pRaInfo->DecisionRate != pRaInfo->PTPreRate)) {
			if (pRaInfo->PTStage == 0)
				pRaInfo->PTStage = 1;
			else if (pRaInfo->PTStage == 1)
				pRaInfo->PTStage = 3;
			else
				pRaInfo->PTStage = 5;

			pRaInfo->PTPreRssi = pRaInfo->RssiStaRA;
			pRaInfo->PTStopCount = 0;
		} else {
			pRaInfo->RAstage = 0;
			pRaInfo->PTStopCount++;
		}
	} else {
		pRaInfo->PTStage = 0;
		pRaInfo->RAstage = 0;
	}
	pRaInfo->PTPreRate = pRaInfo->DecisionRate;
}