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
struct hal_data_8188e {int UsbTxAggMode; int UsbTxAggDescNum; int UsbRxAggBlockCount; int UsbRxAggBlockTimeout; int UsbRxAggPageCount; int UsbRxAggPageTimeout; int /*<<< orphan*/  UsbRxAggMode; int /*<<< orphan*/  interfaceIndex; int /*<<< orphan*/  UsbBulkOutSize; } ;
struct dvobj_priv {int /*<<< orphan*/  RtNumOutPipes; int /*<<< orphan*/  RtNumInPipes; int /*<<< orphan*/  InterfaceNumber; scalar_t__ ishighspeed; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int /*<<< orphan*/  HalUsbSetQueuePipeMapping8188EUsb (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_FULL_SPEED_BULK_SIZE ; 
 int /*<<< orphan*/  USB_HIGH_SPEED_BULK_SIZE ; 
 int /*<<< orphan*/  USB_RX_AGG_DMA ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 

void rtw_hal_chip_configure(struct adapter *adapt)
{
	struct hal_data_8188e *haldata = adapt->HalData;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(adapt);

	if (pdvobjpriv->ishighspeed)
		haldata->UsbBulkOutSize = USB_HIGH_SPEED_BULK_SIZE;/* 512 bytes */
	else
		haldata->UsbBulkOutSize = USB_FULL_SPEED_BULK_SIZE;/* 64 bytes */

	haldata->interfaceIndex = pdvobjpriv->InterfaceNumber;

	haldata->UsbTxAggMode		= 1;
	haldata->UsbTxAggDescNum	= 0x6;	/*  only 4 bits */

	haldata->UsbRxAggMode		= USB_RX_AGG_DMA;/*  USB_RX_AGG_DMA; */
	haldata->UsbRxAggBlockCount	= 8; /* unit : 512b */
	haldata->UsbRxAggBlockTimeout	= 0x6;
	haldata->UsbRxAggPageCount	= 48; /* uint :128 b 0x0A;	10 = MAX_RX_DMA_BUFFER_SIZE/2/haldata->UsbBulkOutSize */
	haldata->UsbRxAggPageTimeout	= 0x4; /* 6, absolute time = 34ms/(2^6) */

	HalUsbSetQueuePipeMapping8188EUsb(adapt,
				pdvobjpriv->RtNumInPipes, pdvobjpriv->RtNumOutPipes);
}