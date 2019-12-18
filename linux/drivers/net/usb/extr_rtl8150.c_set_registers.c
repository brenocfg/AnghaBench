#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  udev; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RTL8150_REQT_WRITE ; 
 int /*<<< orphan*/  RTL8150_REQ_SET_REGS ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_registers(rtl8150_t * dev, u16 indx, u16 size, const void *data)
{
	void *buf;
	int ret;

	buf = kmemdup(data, size, GFP_NOIO);
	if (!buf)
		return -ENOMEM;

	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			      RTL8150_REQ_SET_REGS, RTL8150_REQT_WRITE,
			      indx, 0, buf, size, 500);
	kfree(buf);
	return ret;
}