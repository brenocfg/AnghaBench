#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hal_com_data {scalar_t__ LastHMEBoxNum; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int bFwCurrentInPSMode; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  REG_HMETFR ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

void rtl8723b_InitializeFirmwareVars(struct adapter *padapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);

	/*  Init Fw LPS related. */
	adapter_to_pwrctl(padapter)->bFwCurrentInPSMode = false;

	/* Init H2C cmd. */
	rtw_write8(padapter, REG_HMETFR, 0x0f);

	/*  Init H2C counter. by tynli. 2009.12.09. */
	pHalData->LastHMEBoxNum = 0;
/* pHalData->H2CQueueHead = 0; */
/* pHalData->H2CQueueTail = 0; */
/* pHalData->H2CStopInsertQueue = false; */
}