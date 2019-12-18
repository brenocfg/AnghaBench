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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hal_com_data {size_t pwrGroupCnt; int /*<<< orphan*/ ** MCSTxPowerLevelOriginalOffset; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t PHY_GetRateSectionIndexOfTxPowerByRate (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PHY_StoreTxPowerByRateOld(
	struct adapter *padapter, u32	RegAddr, u32 BitMask, u32 Data
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8	index = PHY_GetRateSectionIndexOfTxPowerByRate(padapter, RegAddr, BitMask);

	pHalData->MCSTxPowerLevelOriginalOffset[pHalData->pwrGroupCnt][index] = Data;
	/* DBG_871X("MCSTxPowerLevelOriginalOffset[%d][0] = 0x%x\n", pHalData->pwrGroupCnt, */
	/*	pHalData->MCSTxPowerLevelOriginalOffset[pHalData->pwrGroupCnt][0]); */
}