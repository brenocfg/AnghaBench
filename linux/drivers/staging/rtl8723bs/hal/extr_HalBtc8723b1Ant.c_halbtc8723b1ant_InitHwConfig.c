#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_13__ {int /*<<< orphan*/  (* fBtcRead1Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcRead4Byte ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* fBtcWrite1ByteBitMask ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_ANT_PATH_BT ; 
 int /*<<< orphan*/  BTC_ANT_PATH_WIFI ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  INTF_INIT ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 int /*<<< orphan*/  halbtc8723b1ant_CoexTableWithType (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc8723b1ant_PsTdma (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  halbtc8723b1ant_SetAntPath (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int) ; 

__attribute__((used)) static void halbtc8723b1ant_InitHwConfig(
	PBTC_COEXIST pBtCoexist,
	bool bBackUp,
	bool bWifiOnly
)
{
	u32 u4Tmp = 0;/*  fwVer; */
	u8 u1Tmpa = 0, u1Tmpb = 0;

	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_INIT,
		("[BTCoex], 1Ant Init HW Config!!\n")
	);

	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x550, 0x8, 0x1);  /* enable TBTT nterrupt */

	/*  0x790[5:0]= 0x5 */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x790, 0x5);

	/*  Enable counter statistics */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x778, 0x1);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x40, 0x20, 0x1);

	/* Antenna config */
	if (bWifiOnly) {
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_WIFI, true, false);
		halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 9);
	} else
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, true, false);

	/*  PTA parameter */
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, FORCE_EXEC, 0);

	u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);
	u1Tmpa = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765);
	u1Tmpb = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x67);

	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_NOTIFY,
		(
			"############# [BTCoex], 0x948 = 0x%x, 0x765 = 0x%x, 0x67 = 0x%x\n",
			u4Tmp,
			u1Tmpa,
			u1Tmpb
		)
	);
}