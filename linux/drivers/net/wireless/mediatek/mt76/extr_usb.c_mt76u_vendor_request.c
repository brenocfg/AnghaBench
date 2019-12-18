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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  usb_ctrl_mtx; } ;
struct mt76_dev {TYPE_1__ usb; } ;

/* Variables and functions */
 int __mt76u_vendor_request (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_usb_reg_wr (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt76u_vendor_request(struct mt76_dev *dev, u8 req,
			 u8 req_type, u16 val, u16 offset,
			 void *buf, size_t len)
{
	int ret;

	mutex_lock(&dev->usb.usb_ctrl_mtx);
	ret = __mt76u_vendor_request(dev, req, req_type,
				     val, offset, buf, len);
	trace_usb_reg_wr(dev, offset, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	return ret;
}