#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW_EXEC ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halbtc8723b2ant_SetFwDacSwingLevel(
	PBTC_COEXIST pBtCoexist, u8 dacSwingLvl
)
{
	u8 	H2C_Parameter[1] = {0};

	/*  There are several type of dacswing */
	/*  0x18/ 0x10/ 0xc/ 0x8/ 0x4/ 0x6 */
	H2C_Parameter[0] = dacSwingLvl;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		("[BTCoex], Set Dac Swing Level = 0x%x\n", dacSwingLvl)
	);
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		("[BTCoex], FW write 0x64 = 0x%x\n", H2C_Parameter[0])
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x64, 1, H2C_Parameter);
}