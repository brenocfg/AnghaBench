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
struct hal_data_8188e {int UsbRxAggMode; int UsbRxAggPageCount; int UsbRxAggPageTimeout; int UsbRxAggBlockCount; int UsbRxAggBlockTimeout; int HwRxPageSize; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
#define  PBP_1024 136 
#define  PBP_128 135 
#define  PBP_256 134 
#define  PBP_512 133 
#define  PBP_64 132 
 int /*<<< orphan*/  REG_RXDMA_AGG_PG_TH ; 
 int /*<<< orphan*/  REG_TRXDMA_CTRL ; 
 int /*<<< orphan*/  REG_USB_AGG_TH ; 
 int /*<<< orphan*/  REG_USB_AGG_TO ; 
 int /*<<< orphan*/  REG_USB_SPECIAL_OPTION ; 
 int RXDMA_AGG_EN ; 
 int USB_AGG_EN ; 
#define  USB_RX_AGG_DISABLE 131 
#define  USB_RX_AGG_DMA 130 
#define  USB_RX_AGG_MIX 129 
#define  USB_RX_AGG_USB 128 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usb_AggSettingRxUpdate(struct adapter *Adapter)
{
	struct hal_data_8188e *haldata = Adapter->HalData;
	u8 valueDMA;
	u8 valueUSB;

	valueDMA = usb_read8(Adapter, REG_TRXDMA_CTRL);
	valueUSB = usb_read8(Adapter, REG_USB_SPECIAL_OPTION);

	switch (haldata->UsbRxAggMode) {
	case USB_RX_AGG_DMA:
		valueDMA |= RXDMA_AGG_EN;
		valueUSB &= ~USB_AGG_EN;
		break;
	case USB_RX_AGG_USB:
		valueDMA &= ~RXDMA_AGG_EN;
		valueUSB |= USB_AGG_EN;
		break;
	case USB_RX_AGG_MIX:
		valueDMA |= RXDMA_AGG_EN;
		valueUSB |= USB_AGG_EN;
		break;
	case USB_RX_AGG_DISABLE:
	default:
		valueDMA &= ~RXDMA_AGG_EN;
		valueUSB &= ~USB_AGG_EN;
		break;
	}

	usb_write8(Adapter, REG_TRXDMA_CTRL, valueDMA);
	usb_write8(Adapter, REG_USB_SPECIAL_OPTION, valueUSB);

	switch (haldata->UsbRxAggMode) {
	case USB_RX_AGG_DMA:
		usb_write8(Adapter, REG_RXDMA_AGG_PG_TH, haldata->UsbRxAggPageCount);
		usb_write8(Adapter, REG_RXDMA_AGG_PG_TH + 1, haldata->UsbRxAggPageTimeout);
		break;
	case USB_RX_AGG_USB:
		usb_write8(Adapter, REG_USB_AGG_TH, haldata->UsbRxAggBlockCount);
		usb_write8(Adapter, REG_USB_AGG_TO, haldata->UsbRxAggBlockTimeout);
		break;
	case USB_RX_AGG_MIX:
		usb_write8(Adapter, REG_RXDMA_AGG_PG_TH, haldata->UsbRxAggPageCount);
		usb_write8(Adapter, REG_RXDMA_AGG_PG_TH + 1, (haldata->UsbRxAggPageTimeout & 0x1F));/* 0x280[12:8] */
		usb_write8(Adapter, REG_USB_AGG_TH, haldata->UsbRxAggBlockCount);
		usb_write8(Adapter, REG_USB_AGG_TO, haldata->UsbRxAggBlockTimeout);
		break;
	case USB_RX_AGG_DISABLE:
	default:
		/*  TODO: */
		break;
	}

	switch (PBP_128) {
	case PBP_128:
		haldata->HwRxPageSize = 128;
		break;
	case PBP_64:
		haldata->HwRxPageSize = 64;
		break;
	case PBP_256:
		haldata->HwRxPageSize = 256;
		break;
	case PBP_512:
		haldata->HwRxPageSize = 512;
		break;
	case PBP_1024:
		haldata->HwRxPageSize = 1024;
		break;
	default:
		break;
	}
}