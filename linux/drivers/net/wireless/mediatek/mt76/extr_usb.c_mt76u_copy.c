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
struct mt76_usb {int /*<<< orphan*/  usb_ctrl_mtx; scalar_t__ data; } ;
struct mt76_dev {struct mt76_usb usb; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  MT_VEND_MULTI_WRITE ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int __mt76u_vendor_request (struct mt76_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned (scalar_t__ const,scalar_t__*) ; 

__attribute__((used)) static void mt76u_copy(struct mt76_dev *dev, u32 offset,
		       const void *data, int len)
{
	struct mt76_usb *usb = &dev->usb;
	const u32 *val = data;
	int i, ret;

	mutex_lock(&usb->usb_ctrl_mtx);
	for (i = 0; i < DIV_ROUND_UP(len, 4); i++) {
		put_unaligned(val[i], (u32 *)usb->data);
		ret = __mt76u_vendor_request(dev, MT_VEND_MULTI_WRITE,
					     USB_DIR_OUT | USB_TYPE_VENDOR,
					     0, offset + i * 4, usb->data,
					     sizeof(u32));
		if (ret < 0)
			break;
	}
	mutex_unlock(&usb->usb_ctrl_mtx);
}