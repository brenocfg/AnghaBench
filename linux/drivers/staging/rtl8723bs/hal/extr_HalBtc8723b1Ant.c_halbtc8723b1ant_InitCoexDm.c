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
struct TYPE_2__ {scalar_t__ popEventCnt; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_CoexTableWithType (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SwMechanism (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pCoexSta ; 

__attribute__((used)) static void halbtc8723b1ant_InitCoexDm(PBTC_COEXIST pBtCoexist)
{
	/*  force to reset coex mechanism */

	/*  sw all off */
	halbtc8723b1ant_SwMechanism(pBtCoexist, false);

	/* halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 8); */
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, FORCE_EXEC, 0);

	pCoexSta->popEventCnt = 0;
}