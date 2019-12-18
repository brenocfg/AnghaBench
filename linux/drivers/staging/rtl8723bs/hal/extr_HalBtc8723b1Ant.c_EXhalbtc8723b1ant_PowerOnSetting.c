#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_16__ {int singleAntPath; void* btdmAntPos; } ;
struct TYPE_15__ {int (* fBtcRead2Byte ) (TYPE_1__*,int) ;scalar_t__ chipInterface; int /*<<< orphan*/  (* fBtcWriteLocalReg1Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcWrite4Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* fBtcWrite2Byte ) (TYPE_1__*,int,int) ;TYPE_2__ boardInfo; } ;
typedef  TYPE_1__* PBTC_COEXIST ;
typedef  TYPE_2__* PBTC_BOARD_INFO ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 void* BTC_ANTENNA_AT_AUX_PORT ; 
 void* BTC_ANTENNA_AT_MAIN_PORT ; 
 scalar_t__ BTC_INTF_PCI ; 
 scalar_t__ BTC_INTF_SDIO ; 
 scalar_t__ BTC_INTF_USB ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__*,int,int) ; 
 int stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__*,int,int) ; 

void EXhalbtc8723b1ant_PowerOnSetting(PBTC_COEXIST pBtCoexist)
{
	PBTC_BOARD_INFO pBoardInfo = &pBtCoexist->boardInfo;
	u8 u1Tmp = 0x0;
	u16 u2Tmp = 0x0;

	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x67, 0x20);

	/*  enable BB, REG_SYS_FUNC_EN such that we can write 0x948 correctly. */
	u2Tmp = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0x2);
	pBtCoexist->fBtcWrite2Byte(pBtCoexist, 0x2, u2Tmp|BIT0|BIT1);

	/*  set GRAN_BT = 1 */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);
	/*  set WLAN_ACT = 0 */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

	/*  */
	/*  S0 or S1 setting and Local register setting(By the setting fw can get ant number, S0/S1, ... info) */
	/*  Local setting bit define */
	/* 	BIT0: "0" for no antenna inverse; "1" for antenna inverse */
	/* 	BIT1: "0" for internal switch; "1" for external switch */
	/* 	BIT2: "0" for one antenna; "1" for two antenna */
	/*  NOTE: here default all internal switch and 1-antenna ==> BIT1 = 0 and BIT2 = 0 */
	if (pBtCoexist->chipInterface == BTC_INTF_USB) {
		/*  fixed at S0 for USB interface */
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);

		u1Tmp |= 0x1;	/*  antenna inverse */
		pBtCoexist->fBtcWriteLocalReg1Byte(pBtCoexist, 0xfe08, u1Tmp);

		pBoardInfo->btdmAntPos = BTC_ANTENNA_AT_AUX_PORT;
	} else {
		/*  for PCIE and SDIO interface, we check efuse 0xc3[6] */
		if (pBoardInfo->singleAntPath == 0) {
			/*  set to S1 */
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280);
			pBoardInfo->btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT;
		} else if (pBoardInfo->singleAntPath == 1) {
			/*  set to S0 */
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);
			u1Tmp |= 0x1;	/*  antenna inverse */
			pBoardInfo->btdmAntPos = BTC_ANTENNA_AT_AUX_PORT;
		}

		if (pBtCoexist->chipInterface == BTC_INTF_PCI)
			pBtCoexist->fBtcWriteLocalReg1Byte(pBtCoexist, 0x384, u1Tmp);
		else if (pBtCoexist->chipInterface == BTC_INTF_SDIO)
			pBtCoexist->fBtcWriteLocalReg1Byte(pBtCoexist, 0x60, u1Tmp);
	}
}