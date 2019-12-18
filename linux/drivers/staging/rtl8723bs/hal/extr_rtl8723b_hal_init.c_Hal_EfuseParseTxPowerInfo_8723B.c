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
struct hal_com_data {int EEPROMRegulatory; int /*<<< orphan*/ ** BW40_24G_Diff; int /*<<< orphan*/ ** BW20_24G_Diff; int /*<<< orphan*/ ** OFDM_24G_Diff; int /*<<< orphan*/ ** CCK_24G_Diff; int /*<<< orphan*/ ** Index24G_BW40_Base; int /*<<< orphan*/ ** Index24G_CCK_Base; } ;
struct adapter {int dummy; } ;
struct TxPowerInfo24G {int /*<<< orphan*/ ** BW40_Diff; int /*<<< orphan*/ ** BW20_Diff; int /*<<< orphan*/ ** OFDM_Diff; int /*<<< orphan*/ ** CCK_Diff; int /*<<< orphan*/ ** IndexBW40_Base; int /*<<< orphan*/ ** IndexCCK_Base; } ;

/* Variables and functions */
 int CHANNEL_MAX_NUMBER ; 
 int EEPROM_DEFAULT_BOARD_OPTION ; 
 size_t EEPROM_RF_BOARD_OPTION_8723B ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  Hal_GetChnlGroup8723B (int,int*) ; 
 int /*<<< orphan*/  Hal_ReadPowerValueFromPROM_8723B (struct adapter*,struct TxPowerInfo24G*,int*,int) ; 
 int MAX_RF_PATH ; 
 int MAX_TX_COUNT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

void Hal_EfuseParseTxPowerInfo_8723B(
	struct adapter *padapter, u8 *PROMContent, bool AutoLoadFail
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	struct TxPowerInfo24G	pwrInfo24G;
	u8 	rfPath, ch, TxCount = 1;

	Hal_ReadPowerValueFromPROM_8723B(padapter, &pwrInfo24G, PROMContent, AutoLoadFail);
	for (rfPath = 0 ; rfPath < MAX_RF_PATH ; rfPath++) {
		for (ch = 0 ; ch < CHANNEL_MAX_NUMBER; ch++) {
			u8 group = 0;

			Hal_GetChnlGroup8723B(ch+1, &group);

			if (ch == 14-1) {
				pHalData->Index24G_CCK_Base[rfPath][ch] = pwrInfo24G.IndexCCK_Base[rfPath][5];
				pHalData->Index24G_BW40_Base[rfPath][ch] = pwrInfo24G.IndexBW40_Base[rfPath][group];
			} else {
				pHalData->Index24G_CCK_Base[rfPath][ch] = pwrInfo24G.IndexCCK_Base[rfPath][group];
				pHalData->Index24G_BW40_Base[rfPath][ch] = pwrInfo24G.IndexBW40_Base[rfPath][group];
			}
#ifdef DEBUG
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("======= Path %d, ChannelIndex %d, Group %d =======\n", rfPath, ch, group));
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("Index24G_CCK_Base[%d][%d] = 0x%x\n", rfPath, ch, pHalData->Index24G_CCK_Base[rfPath][ch]));
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("Index24G_BW40_Base[%d][%d] = 0x%x\n", rfPath, ch, pHalData->Index24G_BW40_Base[rfPath][ch]));
#endif
		}

		for (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) {
			pHalData->CCK_24G_Diff[rfPath][TxCount] = pwrInfo24G.CCK_Diff[rfPath][TxCount];
			pHalData->OFDM_24G_Diff[rfPath][TxCount] = pwrInfo24G.OFDM_Diff[rfPath][TxCount];
			pHalData->BW20_24G_Diff[rfPath][TxCount] = pwrInfo24G.BW20_Diff[rfPath][TxCount];
			pHalData->BW40_24G_Diff[rfPath][TxCount] = pwrInfo24G.BW40_Diff[rfPath][TxCount];

#ifdef DEBUG
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("--------------------------------------- 2.4G ---------------------------------------\n"));
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("CCK_24G_Diff[%d][%d]= %d\n", rfPath, TxCount, pHalData->CCK_24G_Diff[rfPath][TxCount]));
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("OFDM_24G_Diff[%d][%d]= %d\n", rfPath, TxCount, pHalData->OFDM_24G_Diff[rfPath][TxCount]));
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("BW20_24G_Diff[%d][%d]= %d\n", rfPath, TxCount, pHalData->BW20_24G_Diff[rfPath][TxCount]));
			RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("BW40_24G_Diff[%d][%d]= %d\n", rfPath, TxCount, pHalData->BW40_24G_Diff[rfPath][TxCount]));
#endif
		}
	}

	/*  2010/10/19 MH Add Regulator recognize for CU. */
	if (!AutoLoadFail) {
		pHalData->EEPROMRegulatory = (PROMContent[EEPROM_RF_BOARD_OPTION_8723B]&0x7);	/* bit0~2 */
		if (PROMContent[EEPROM_RF_BOARD_OPTION_8723B] == 0xFF)
			pHalData->EEPROMRegulatory = (EEPROM_DEFAULT_BOARD_OPTION&0x7);	/* bit0~2 */
	} else
		pHalData->EEPROMRegulatory = 0;

	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_, ("EEPROMRegulatory = 0x%x\n", pHalData->EEPROMRegulatory));
}