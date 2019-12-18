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
typedef  int u8 ;
struct TYPE_2__ {int curAlgorithm; int preAlgorithm; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  BT_8723B_1ANT_COEX_ALGO_A2DP 137 
#define  BT_8723B_1ANT_COEX_ALGO_A2DP_PANHS 136 
#define  BT_8723B_1ANT_COEX_ALGO_HID 135 
#define  BT_8723B_1ANT_COEX_ALGO_HID_A2DP 134 
#define  BT_8723B_1ANT_COEX_ALGO_HID_A2DP_PANEDR 133 
#define  BT_8723B_1ANT_COEX_ALGO_PANEDR 132 
#define  BT_8723B_1ANT_COEX_ALGO_PANEDR_A2DP 131 
#define  BT_8723B_1ANT_COEX_ALGO_PANEDR_HID 130 
#define  BT_8723B_1ANT_COEX_ALGO_PANHS 129 
#define  BT_8723B_1ANT_COEX_ALGO_SCO 128 
 int halbtc8723b1ant_ActionAlgorithm (int /*<<< orphan*/ ) ; 
 scalar_t__ halbtc8723b1ant_IsCommonAction (int /*<<< orphan*/ ) ; 
 TYPE_1__* pCoexDm ; 

__attribute__((used)) static void halbtc8723b1ant_RunSwCoexistMechanism(PBTC_COEXIST pBtCoexist)
{
	u8 algorithm = 0;

	algorithm = halbtc8723b1ant_ActionAlgorithm(pBtCoexist);
	pCoexDm->curAlgorithm = algorithm;

	if (halbtc8723b1ant_IsCommonAction(pBtCoexist)) {

	} else {
		switch (pCoexDm->curAlgorithm) {
		case BT_8723B_1ANT_COEX_ALGO_SCO:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = SCO.\n"));
			/* halbtc8723b1ant_ActionSco(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_HID:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HID.\n"));
			/* halbtc8723b1ant_ActionHid(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = A2DP.\n"));
			/* halbtc8723b1ant_ActionA2dp(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_A2DP_PANHS:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = A2DP+PAN(HS).\n"));
			/* halbtc8723b1ant_ActionA2dpPanHs(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_PANEDR:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = PAN(EDR).\n"));
			/* halbtc8723b1ant_ActionPanEdr(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_PANHS:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HS mode.\n"));
			/* halbtc8723b1ant_ActionPanHs(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_PANEDR_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = PAN+A2DP.\n"));
			/* halbtc8723b1ant_ActionPanEdrA2dp(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_PANEDR_HID:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = PAN(EDR)+HID.\n"));
			/* halbtc8723b1ant_ActionPanEdrHid(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_HID_A2DP_PANEDR:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HID+A2DP+PAN.\n"));
			/* halbtc8723b1ant_ActionHidA2dpPanEdr(pBtCoexist); */
			break;
		case BT_8723B_1ANT_COEX_ALGO_HID_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HID+A2DP.\n"));
			/* halbtc8723b1ant_ActionHidA2dp(pBtCoexist); */
			break;
		default:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = coexist All Off!!\n"));
			break;
		}
		pCoexDm->preAlgorithm = pCoexDm->curAlgorithm;
	}
}