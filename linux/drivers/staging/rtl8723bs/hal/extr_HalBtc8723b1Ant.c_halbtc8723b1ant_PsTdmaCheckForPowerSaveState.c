#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  (* fBtcGet ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_GET_U1_LPS_MODE ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_PsTdmaCheckForPowerSaveState(
	PBTC_COEXIST pBtCoexist, bool bNewPsState
)
{
	u8 lpsMode = 0x0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_LPS_MODE, &lpsMode);

	if (lpsMode) {	/*  already under LPS state */
		if (bNewPsState) {
			/*  keep state under LPS, do nothing. */
		} else /*  will leave LPS state, turn off psTdma first */
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
	} else {						/*  NO PS state */
		if (bNewPsState) /*  will enter LPS state, turn off psTdma first */
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
		else {
			/*  keep state under NO PS state, do nothing. */
		}
	}
}