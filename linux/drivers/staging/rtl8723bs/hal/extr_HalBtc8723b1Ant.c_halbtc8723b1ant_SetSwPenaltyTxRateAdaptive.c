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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,int*) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW_EXEC ; 
 int BIT0 ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int*) ; 

__attribute__((used)) static void halbtc8723b1ant_SetSwPenaltyTxRateAdaptive(
	PBTC_COEXIST pBtCoexist, bool bLowPenaltyRa
)
{
	u8 	H2C_Parameter[6] = {0};

	H2C_Parameter[0] = 0x6;	/*  opCode, 0x6 = Retry_Penalty */

	if (bLowPenaltyRa) {
		H2C_Parameter[1] |= BIT0;
		H2C_Parameter[2] = 0x00;  /* normal rate except MCS7/6/5, OFDM54/48/36 */
		H2C_Parameter[3] = 0xf7;  /* MCS7 or OFDM54 */
		H2C_Parameter[4] = 0xf8;  /* MCS6 or OFDM48 */
		H2C_Parameter[5] = 0xf9;	/* MCS5 or OFDM36 */
	}

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], set WiFi Low-Penalty Retry: %s",
			(bLowPenaltyRa ? "ON!!" : "OFF!!")
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x69, 6, H2C_Parameter);
}