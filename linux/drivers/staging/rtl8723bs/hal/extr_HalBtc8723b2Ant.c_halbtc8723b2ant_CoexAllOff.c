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
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b2ant_CoexTableWithType (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DecBtPwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b2ant_FwDacSwingLvl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_PsTdma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism1 (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_SwMechanism2 (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void halbtc8723b2ant_CoexAllOff(PBTC_COEXIST pBtCoexist)
{
	/*  fw all off */
	halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
	halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	/*  sw all off */
	halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
	halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

	/*  hw all off */
	/* pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0); */
	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
}