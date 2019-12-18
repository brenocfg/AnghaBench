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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  usb_ctrl_mtx; } ;
struct mt76_dev {TYPE_1__ usb; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  __mt76u_vendor_request (struct mt76_dev*,int /*<<< orphan*/  const,int,int const,scalar_t__ const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mt76u_single_wr(struct mt76_dev *dev, const u8 req,
		     const u16 offset, const u32 val)
{
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	__mt76u_vendor_request(dev, req,
			       USB_DIR_OUT | USB_TYPE_VENDOR,
			       val & 0xffff, offset, NULL, 0);
	__mt76u_vendor_request(dev, req,
			       USB_DIR_OUT | USB_TYPE_VENDOR,
			       val >> 16, offset + 2, NULL, 0);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);
}