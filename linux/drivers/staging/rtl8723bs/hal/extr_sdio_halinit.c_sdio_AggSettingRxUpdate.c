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
struct hal_com_data {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  REG_RXDMA_MODE_CTRL_8723B ; 
 int /*<<< orphan*/  REG_TRXDMA_CTRL ; 
 int RXDMA_AGG_EN ; 
 int RXDMA_AGG_MODE_EN ; 
 int rtw_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdio_AggSettingRxUpdate(struct adapter *padapter)
{
	struct hal_com_data *pHalData;
	u8 valueDMA;
	u8 valueRxAggCtrl = 0;
	u8 aggBurstNum = 3;  /* 0:1, 1:2, 2:3, 3:4 */
	u8 aggBurstSize = 0;  /* 0:1K, 1:512Byte, 2:256Byte... */

	pHalData = GET_HAL_DATA(padapter);

	valueDMA = rtw_read8(padapter, REG_TRXDMA_CTRL);
	valueDMA |= RXDMA_AGG_EN;
	rtw_write8(padapter, REG_TRXDMA_CTRL, valueDMA);

	valueRxAggCtrl |= RXDMA_AGG_MODE_EN;
	valueRxAggCtrl |= ((aggBurstNum << 2) & 0x0C);
	valueRxAggCtrl |= ((aggBurstSize << 4) & 0x30);
	rtw_write8(padapter, REG_RXDMA_MODE_CTRL_8723B, valueRxAggCtrl);/* RxAggLowThresh = 4*1K */
}