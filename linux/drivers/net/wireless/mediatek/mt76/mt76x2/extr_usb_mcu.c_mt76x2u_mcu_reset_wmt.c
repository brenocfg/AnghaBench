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
typedef  int u8 ;
struct mt76_usb {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct mt76_usb usb; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VEND_DEV_MODE ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mt76u_vendor_request (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x2u_mcu_reset_wmt(struct mt76x02_dev *dev)
{
	struct mt76_usb *usb = &dev->mt76.usb;
	u8 data[] = {
		0x6f, 0xfc, 0x05, 0x01,
		0x07, 0x01, 0x00, 0x04
	};

	memcpy(usb->data, data, sizeof(data));
	mt76u_vendor_request(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_DIR_OUT | USB_TYPE_CLASS,
			     0x12, 0, usb->data, sizeof(data));
}