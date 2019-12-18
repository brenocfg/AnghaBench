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
struct hal_com_data {scalar_t__ SdioRxFIFOCnt; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  rtl8723b_init_default_value (struct adapter*) ; 

__attribute__((used)) static void rtl8723bs_init_default_value(struct adapter *padapter)
{
	struct hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);

	rtl8723b_init_default_value(padapter);

	/*  interface related variable */
	pHalData->SdioRxFIFOCnt = 0;
}