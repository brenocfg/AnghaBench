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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hal_com_data {int* sdio_tx_max_len; } ;
struct dvobj_priv {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 size_t HI_QUEUE_IDX ; 
 size_t LOW_QUEUE_IDX ; 
 size_t MID_QUEUE_IDX ; 
#define  WLAN_TX_HIQ_DEVICE_ID 130 
#define  WLAN_TX_LOQ_DEVICE_ID 129 
#define  WLAN_TX_MIQ_DEVICE_ID 128 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int ffaddr2deviceId (struct dvobj_priv*,int /*<<< orphan*/ ) ; 

u32 rtw_hal_get_sdio_tx_max_length(struct adapter *padapter, u8 queue_idx)
{
	struct dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);
	struct hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u32 deviceId, max_len;


	deviceId = ffaddr2deviceId(pdvobjpriv, queue_idx);
	switch (deviceId) {
	case WLAN_TX_HIQ_DEVICE_ID:
		max_len = pHalData->sdio_tx_max_len[HI_QUEUE_IDX];
		break;

	case WLAN_TX_MIQ_DEVICE_ID:
		max_len = pHalData->sdio_tx_max_len[MID_QUEUE_IDX];
		break;

	case WLAN_TX_LOQ_DEVICE_ID:
		max_len = pHalData->sdio_tx_max_len[LOW_QUEUE_IDX];
		break;

	default:
		max_len = pHalData->sdio_tx_max_len[MID_QUEUE_IDX];
		break;
	}

	return max_len;
}