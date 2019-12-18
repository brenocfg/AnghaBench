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
struct hal_com_data {scalar_t__ CurrentChannelBW; scalar_t__ nCur80MhzPrimeSC; scalar_t__ nCur40MhzPrimeSC; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_WIDTH_40 ; 
 scalar_t__ CHANNEL_WIDTH_80 ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_UPPER ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int VHT_DATA_SC_20_LOWER_OF_80MHZ ; 
 int VHT_DATA_SC_20_LOWEST_OF_80MHZ ; 
 int VHT_DATA_SC_20_UPPERST_OF_80MHZ ; 
 int VHT_DATA_SC_20_UPPER_OF_80MHZ ; 
 int VHT_DATA_SC_40_LOWER_OF_80MHZ ; 
 int VHT_DATA_SC_40_UPPER_OF_80MHZ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 

__attribute__((used)) static u8 phy_GetSecondaryChnl_8723B(struct adapter *Adapter)
{
	u8 SCSettingOf40 = 0, SCSettingOf20 = 0;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	RT_TRACE(
		_module_hal_init_c_,
		_drv_info_,
		(
			"SCMapping: VHT Case: pHalData->CurrentChannelBW %d, pHalData->nCur80MhzPrimeSC %d, pHalData->nCur40MhzPrimeSC %d\n",
			pHalData->CurrentChannelBW,
			pHalData->nCur80MhzPrimeSC,
			pHalData->nCur40MhzPrimeSC
		)
	);
	if (pHalData->CurrentChannelBW == CHANNEL_WIDTH_80) {
		if (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
			SCSettingOf40 = VHT_DATA_SC_40_LOWER_OF_80MHZ;
		else if (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
			SCSettingOf40 = VHT_DATA_SC_40_UPPER_OF_80MHZ;
		else
			RT_TRACE(_module_hal_init_c_, _drv_err_, ("SCMapping: Not Correct Primary40MHz Setting\n"));

		if (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_LOWEST_OF_80MHZ;
		else if (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		else if (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		else if (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_UPPERST_OF_80MHZ;
		else
			RT_TRACE(_module_hal_init_c_, _drv_err_, ("SCMapping: Not Correct Primary40MHz Setting\n"));
	} else if (pHalData->CurrentChannelBW == CHANNEL_WIDTH_40) {
		RT_TRACE(
			_module_hal_init_c_,
			_drv_info_,
			(
				"SCMapping: VHT Case: pHalData->CurrentChannelBW %d, pHalData->nCur40MhzPrimeSC %d\n",
				pHalData->CurrentChannelBW,
				pHalData->nCur40MhzPrimeSC
			)
		);

		if (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
			SCSettingOf20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		else if (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
			SCSettingOf20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		else
			RT_TRACE(_module_hal_init_c_, _drv_err_, ("SCMapping: Not Correct Primary40MHz Setting\n"));
	}

	RT_TRACE(_module_hal_init_c_, _drv_info_, ("SCMapping: SC Value %x\n", ((SCSettingOf40 << 4) | SCSettingOf20)));
	return  (SCSettingOf40 << 4) | SCSettingOf20;
}