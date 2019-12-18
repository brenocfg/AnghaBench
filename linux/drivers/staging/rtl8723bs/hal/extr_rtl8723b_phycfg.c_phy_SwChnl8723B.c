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
typedef  int u8 ;
struct hal_com_data {int CurrentChannel; scalar_t__ rf_chip; int* RfRegChnlVal; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,int) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RF_PATH_B ; 
 int /*<<< orphan*/  PHY_SetRFReg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 scalar_t__ RF_PSEUDO_11N ; 

__attribute__((used)) static void phy_SwChnl8723B(struct adapter *padapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 channelToSW = pHalData->CurrentChannel;

	if (pHalData->rf_chip == RF_PSEUDO_11N) {
		/* RT_TRACE(COMP_MLME, DBG_LOUD, ("phy_SwChnl8723B: return for PSEUDO\n")); */
		return;
	}
	pHalData->RfRegChnlVal[0] = ((pHalData->RfRegChnlVal[0] & 0xfffff00) | channelToSW);
	PHY_SetRFReg(padapter, ODM_RF_PATH_A, RF_CHNLBW, 0x3FF, pHalData->RfRegChnlVal[0]);
	PHY_SetRFReg(padapter, ODM_RF_PATH_B, RF_CHNLBW, 0x3FF, pHalData->RfRegChnlVal[0]);

	DBG_8192C("===>phy_SwChnl8723B: Channel = %d\n", channelToSW);
}