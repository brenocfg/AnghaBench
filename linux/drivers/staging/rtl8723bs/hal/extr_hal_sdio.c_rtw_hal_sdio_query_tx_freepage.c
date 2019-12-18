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
typedef  size_t u8 ;
struct hal_com_data {size_t* SdioTxFIFOFreePage; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t PUBLIC_QUEUE_IDX ; 

u8 rtw_hal_sdio_query_tx_freepage(
	struct adapter *padapter, u8 PageIdx, u8 RequiredPageNum
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	if ((pHalData->SdioTxFIFOFreePage[PageIdx]+pHalData->SdioTxFIFOFreePage[PUBLIC_QUEUE_IDX]) >= (RequiredPageNum))
		return true;
	else
		return false;
}