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
struct hal_com_data {int /*<<< orphan*/  SysIntrMask; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 

void InitSysInterrupt8723BSdio(struct adapter *adapter)
{
	struct hal_com_data *haldata;


	haldata = GET_HAL_DATA(adapter);

	haldata->SysIntrMask = (		\
/* 							HSIMR_GPIO12_0_INT_EN			| */
/* 							HSIMR_SPS_OCP_INT_EN			| */
/* 							HSIMR_RON_INT_EN				| */
/* 							HSIMR_PDNINT_EN				| */
/* 							HSIMR_GPIO9_INT_EN				| */
							0);
}