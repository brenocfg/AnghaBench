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
typedef  scalar_t__ u32 ;
struct hal_data_8188e {scalar_t__** MCSTxPowerLevelOriginalOffset; size_t pwrGroupCnt; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 scalar_t__ rTxAGC_A_CCK1_Mcs32 ; 
 scalar_t__ rTxAGC_A_Mcs03_Mcs00 ; 
 scalar_t__ rTxAGC_A_Mcs07_Mcs04 ; 
 scalar_t__ rTxAGC_A_Mcs11_Mcs08 ; 
 scalar_t__ rTxAGC_A_Mcs15_Mcs12 ; 
 scalar_t__ rTxAGC_A_Rate18_06 ; 
 scalar_t__ rTxAGC_A_Rate54_24 ; 
 scalar_t__ rTxAGC_B_CCK11_A_CCK2_11 ; 
 scalar_t__ rTxAGC_B_CCK1_55_Mcs32 ; 
 scalar_t__ rTxAGC_B_Mcs03_Mcs00 ; 
 scalar_t__ rTxAGC_B_Mcs07_Mcs04 ; 
 scalar_t__ rTxAGC_B_Mcs11_Mcs08 ; 
 scalar_t__ rTxAGC_B_Mcs15_Mcs12 ; 
 scalar_t__ rTxAGC_B_Rate18_06 ; 
 scalar_t__ rTxAGC_B_Rate54_24 ; 

__attribute__((used)) static void store_pwrindex_offset(struct adapter *adapter,
				  u32 regaddr, u32 bitmask, u32 data)
{
	struct hal_data_8188e *hal_data = adapter->HalData;
	u32 * const power_level_offset =
		hal_data->MCSTxPowerLevelOriginalOffset[hal_data->pwrGroupCnt];

	if (regaddr == rTxAGC_A_Rate18_06)
		power_level_offset[0] = data;
	if (regaddr == rTxAGC_A_Rate54_24)
		power_level_offset[1] = data;
	if (regaddr == rTxAGC_A_CCK1_Mcs32)
		power_level_offset[6] = data;
	if (regaddr == rTxAGC_B_CCK11_A_CCK2_11 && bitmask == 0xffffff00)
		power_level_offset[7] = data;
	if (regaddr == rTxAGC_A_Mcs03_Mcs00)
		power_level_offset[2] = data;
	if (regaddr == rTxAGC_A_Mcs07_Mcs04)
		power_level_offset[3] = data;
	if (regaddr == rTxAGC_A_Mcs11_Mcs08)
		power_level_offset[4] = data;
	if (regaddr == rTxAGC_A_Mcs15_Mcs12) {
		power_level_offset[5] = data;
		hal_data->pwrGroupCnt++;
	}
	if (regaddr == rTxAGC_B_Rate18_06)
		power_level_offset[8] = data;
	if (regaddr == rTxAGC_B_Rate54_24)
		power_level_offset[9] = data;
	if (regaddr == rTxAGC_B_CCK1_55_Mcs32)
		power_level_offset[14] = data;
	if (regaddr == rTxAGC_B_CCK11_A_CCK2_11 && bitmask == 0x000000ff)
		power_level_offset[15] = data;
	if (regaddr == rTxAGC_B_Mcs03_Mcs00)
		power_level_offset[10] = data;
	if (regaddr == rTxAGC_B_Mcs07_Mcs04)
		power_level_offset[11] = data;
	if (regaddr == rTxAGC_B_Mcs11_Mcs08)
		power_level_offset[12] = data;
	if (regaddr == rTxAGC_B_Mcs15_Mcs12)
		power_level_offset[13] = data;
}