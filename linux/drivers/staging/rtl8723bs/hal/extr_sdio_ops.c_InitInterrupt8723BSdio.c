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
struct hal_com_data {scalar_t__ sdio_himr; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int SDIO_HIMR_AVAL_MSK ; 
 int SDIO_HIMR_RX_REQUEST_MSK ; 

void InitInterrupt8723BSdio(struct adapter *adapter)
{
	struct hal_com_data *haldata;


	haldata = GET_HAL_DATA(adapter);
	haldata->sdio_himr = (u32)(		\
								SDIO_HIMR_RX_REQUEST_MSK			|
								SDIO_HIMR_AVAL_MSK					|
/* 								SDIO_HIMR_TXERR_MSK				| */
/* 								SDIO_HIMR_RXERR_MSK				| */
/* 								SDIO_HIMR_TXFOVW_MSK				| */
/* 								SDIO_HIMR_RXFOVW_MSK				| */
/* 								SDIO_HIMR_TXBCNOK_MSK				| */
/* 								SDIO_HIMR_TXBCNERR_MSK			| */
/* 								SDIO_HIMR_BCNERLY_INT_MSK			| */
/* 								SDIO_HIMR_C2HCMD_MSK				| */
/* 								SDIO_HIMR_HSISR_IND_MSK			| */
/* 								SDIO_HIMR_GTINT3_IND_MSK			| */
/* 								SDIO_HIMR_GTINT4_IND_MSK			| */
/* 								SDIO_HIMR_PSTIMEOUT_MSK			| */
/* 								SDIO_HIMR_OCPINT_MSK				| */
/* 								SDIO_HIMR_ATIMEND_MSK				| */
/* 								SDIO_HIMR_ATIMEND_E_MSK			| */
/* 								SDIO_HIMR_CTWEND_MSK				| */
								0);
}