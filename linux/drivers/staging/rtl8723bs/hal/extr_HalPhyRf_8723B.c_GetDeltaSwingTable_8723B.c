#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hal_com_data {int CurrentChannel; } ;
struct adapter {int dummy; } ;
struct TYPE_4__ {int* DeltaSwingTableIdx_2GCCKA_P; int* DeltaSwingTableIdx_2GCCKA_N; int* DeltaSwingTableIdx_2GCCKB_P; int* DeltaSwingTableIdx_2GCCKB_N; int* DeltaSwingTableIdx_2GA_P; int* DeltaSwingTableIdx_2GA_N; int* DeltaSwingTableIdx_2GB_P; int* DeltaSwingTableIdx_2GB_N; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pForcedDataRate; TYPE_1__ RFCalibrateInfo; struct adapter* Adapter; } ;
typedef  TYPE_1__* PODM_RF_CAL_T ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 scalar_t__ DeltaSwingTableIdx_2GA_N_8188E ; 
 scalar_t__ DeltaSwingTableIdx_2GA_P_8188E ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ IS_CCK_RATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void GetDeltaSwingTable_8723B(
	PDM_ODM_T pDM_Odm,
	u8 **TemperatureUP_A,
	u8 **TemperatureDOWN_A,
	u8 **TemperatureUP_B,
	u8 **TemperatureDOWN_B
)
{
	struct adapter *Adapter = pDM_Odm->Adapter;
	PODM_RF_CAL_T pRFCalibrateInfo = &(pDM_Odm->RFCalibrateInfo);
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	u16 rate = *(pDM_Odm->pForcedDataRate);
	u8 channel = pHalData->CurrentChannel;

	if (1 <= channel && channel <= 14) {
		if (IS_CCK_RATE(rate)) {
			*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKA_P;
			*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKA_N;
			*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKB_P;
			*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKB_N;
		} else {
			*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_2GA_P;
			*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_2GA_N;
			*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_2GB_P;
			*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_2GB_N;
		}
	} /*else if (36 <= channel && channel <= 64) {
		*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[0];
		*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[0];
		*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[0];
		*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[0];
	} else if (100 <= channel && channel <= 140) {
		*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[1];
		*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[1];
		*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[1];
		*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[1];
	} else if (149 <= channel && channel <= 173) {
		*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[2];
		*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[2];
		*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[2];
		*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[2];
	}*/else {
		*TemperatureUP_A   = (u8 *)DeltaSwingTableIdx_2GA_P_8188E;
		*TemperatureDOWN_A = (u8 *)DeltaSwingTableIdx_2GA_N_8188E;
		*TemperatureUP_B   = (u8 *)DeltaSwingTableIdx_2GA_P_8188E;
		*TemperatureDOWN_B = (u8 *)DeltaSwingTableIdx_2GA_N_8188E;
	}

	return;
}