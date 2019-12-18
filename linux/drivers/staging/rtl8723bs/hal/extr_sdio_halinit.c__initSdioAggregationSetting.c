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
struct hal_com_data {int UsbRxHighSpeedMode; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  HalRxAggr8723BSdio (struct adapter*) ; 
 int /*<<< orphan*/  sdio_AggSettingRxUpdate (struct adapter*) ; 

__attribute__((used)) static void _initSdioAggregationSetting(struct adapter *padapter)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	/*  Tx aggregation setting */
/* 	sdio_AggSettingTxUpdate(padapter); */

	/*  Rx aggregation setting */
	HalRxAggr8723BSdio(padapter);

	sdio_AggSettingRxUpdate(padapter);

	/*  201/12/10 MH Add for USB agg mode dynamic switch. */
	pHalData->UsbRxHighSpeedMode = false;
}