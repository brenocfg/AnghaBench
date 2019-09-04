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
typedef  int u32 ;
typedef  int u16 ;
struct msi2500_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  msi2500_dbg_usb_control_msg (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msi2500_ctrl_msg(struct msi2500_dev *dev, u8 cmd, u32 data)
{
	int ret;
	u8 request = cmd;
	u8 requesttype = USB_DIR_OUT | USB_TYPE_VENDOR;
	u16 value = (data >> 0) & 0xffff;
	u16 index = (data >> 16) & 0xffff;

	msi2500_dbg_usb_control_msg(dev->dev, request, requesttype,
				    value, index, NULL, 0);
	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0), request,
			      requesttype, value, index, NULL, 0, 2000);
	if (ret)
		dev_err(dev->dev, "failed %d, cmd %02x, data %04x\n",
			ret, cmd, data);

	return ret;
}