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
struct TYPE_2__ {int bCurLowPenaltyRa; int bPreLowPenaltyRa; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc8723b1ant_SetSwPenaltyTxRateAdaptive (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pCoexDm ; 

__attribute__((used)) static void halbtc8723b1ant_LowPenaltyRa(
	PBTC_COEXIST pBtCoexist, bool bForceExec, bool bLowPenaltyRa
)
{
	pCoexDm->bCurLowPenaltyRa = bLowPenaltyRa;

	if (!bForceExec) {
		if (pCoexDm->bPreLowPenaltyRa == pCoexDm->bCurLowPenaltyRa)
			return;
	}
	halbtc8723b1ant_SetSwPenaltyTxRateAdaptive(
		pBtCoexist, pCoexDm->bCurLowPenaltyRa
	);

	pCoexDm->bPreLowPenaltyRa = pCoexDm->bCurLowPenaltyRa;
}