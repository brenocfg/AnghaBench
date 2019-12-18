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
typedef  size_t u8 ;
struct hal_com_data {int /*<<< orphan*/  EEPROMThermalMeter; } ;
struct TYPE_4__ {int /*<<< orphan*/  ThermalValue_LCK; int /*<<< orphan*/  ThermalValue_IQK; int /*<<< orphan*/  ThermalValue; scalar_t__* PowerIndexOffset; scalar_t__* DeltaPowerIndexLast; scalar_t__* DeltaPowerIndex; int /*<<< orphan*/ * OFDM_index; scalar_t__ CCK_index; } ;
struct TYPE_5__ {int Modify_TxAGC_Flag_PathA; int Modify_TxAGC_Flag_PathB; TYPE_1__ RFCalibrateInfo; scalar_t__ Remnant_CCKSwingIdx; scalar_t__* Remnant_OFDMSwingIdx; scalar_t__* Absolute_OFDMSwingIdx; int /*<<< orphan*/  DefaultOfdmIndex; int /*<<< orphan*/ * BbSwingIdxOfdm; int /*<<< orphan*/ * BbSwingIdxOfdmBase; int /*<<< orphan*/  DefaultCckIndex; int /*<<< orphan*/  BbSwingIdxCck; int /*<<< orphan*/  BbSwingIdxCckBase; int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (int /*<<< orphan*/ ) ; 
 size_t MAX_RF_PATH ; 
 size_t ODM_RF_PATH_A ; 

void ODM_ClearTxPowerTrackingState(PDM_ODM_T pDM_Odm)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(pDM_Odm->Adapter);
	u8 p = 0;

	pDM_Odm->BbSwingIdxCckBase = pDM_Odm->DefaultCckIndex;
	pDM_Odm->BbSwingIdxCck = pDM_Odm->DefaultCckIndex;
	pDM_Odm->RFCalibrateInfo.CCK_index = 0;

	for (p = ODM_RF_PATH_A; p < MAX_RF_PATH; ++p) {
		pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->DefaultOfdmIndex;
		pDM_Odm->BbSwingIdxOfdm[p] = pDM_Odm->DefaultOfdmIndex;
		pDM_Odm->RFCalibrateInfo.OFDM_index[p] = pDM_Odm->DefaultOfdmIndex;

		pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;
		pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[p] = 0;
		pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[p] = 0;
		pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;

		/*  Initial Mix mode power tracking */
		pDM_Odm->Absolute_OFDMSwingIdx[p] = 0;
		pDM_Odm->Remnant_OFDMSwingIdx[p] = 0;
	}

	/* Initial at Modify Tx Scaling Mode */
	pDM_Odm->Modify_TxAGC_Flag_PathA = false;
	/* Initial at Modify Tx Scaling Mode */
	pDM_Odm->Modify_TxAGC_Flag_PathB = false;
	pDM_Odm->Remnant_CCKSwingIdx = 0;
	pDM_Odm->RFCalibrateInfo.ThermalValue = pHalData->EEPROMThermalMeter;
	pDM_Odm->RFCalibrateInfo.ThermalValue_IQK = pHalData->EEPROMThermalMeter;
	pDM_Odm->RFCalibrateInfo.ThermalValue_LCK = pHalData->EEPROMThermalMeter;
}