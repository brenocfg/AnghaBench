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
typedef  int u16 ;
struct hal_com_data {void* RegCR_1; void* RegReg542; void* RegFwHwTxQCtrl; void* RegTxPause; void* RegBcnCtrlVal; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_DMA_ATIME_INT_TIME_8723B ; 
 int DIS_TSF_UDT ; 
 int /*<<< orphan*/  DRIVER_EARLY_INT_TIME_8723B ; 
 int EN_BCN_FUNCTION ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  REG_BCNDMATIM ; 
 scalar_t__ REG_BCNTCFG ; 
 scalar_t__ REG_BCN_CTRL ; 
 scalar_t__ REG_CR ; 
 int /*<<< orphan*/  REG_DRVERLYINT ; 
 scalar_t__ REG_FWHW_TXQ_CTRL ; 
 scalar_t__ REG_TBTT_PROHIBIT ; 
 scalar_t__ REG_TXPAUSE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* rtw_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8723b_InitBeaconParameters(struct adapter *padapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u16 val16;
	u8 val8;


	val8 = DIS_TSF_UDT;
	val16 = val8 | (val8 << 8); /*  port0 and port1 */

	/*  Enable prot0 beacon function for PSTDMA */
	val16 |= EN_BCN_FUNCTION;

	rtw_write16(padapter, REG_BCN_CTRL, val16);

	/*  TODO: Remove these magic number */
	rtw_write16(padapter, REG_TBTT_PROHIBIT, 0x6404);/*  ms */
	/*  Firmware will control REG_DRVERLYINT when power saving is enable, */
	/*  so don't set this register on STA mode. */
	if (check_fwstate(&padapter->mlmepriv, WIFI_STATION_STATE) == false)
		rtw_write8(padapter, REG_DRVERLYINT, DRIVER_EARLY_INT_TIME_8723B); /*  5ms */
	rtw_write8(padapter, REG_BCNDMATIM, BCN_DMA_ATIME_INT_TIME_8723B); /*  2ms */

	/*  Suggested by designer timchen. Change beacon AIFS to the largest number */
	/*  beacause test chip does not contension before sending beacon. by tynli. 2009.11.03 */
	rtw_write16(padapter, REG_BCNTCFG, 0x660F);

	pHalData->RegBcnCtrlVal = rtw_read8(padapter, REG_BCN_CTRL);
	pHalData->RegTxPause = rtw_read8(padapter, REG_TXPAUSE);
	pHalData->RegFwHwTxQCtrl = rtw_read8(padapter, REG_FWHW_TXQ_CTRL+2);
	pHalData->RegReg542 = rtw_read8(padapter, REG_TBTT_PROHIBIT+2);
	pHalData->RegCR_1 = rtw_read8(padapter, REG_CR+1);
}