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
typedef  int u16 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OPERA_READ_MSG ; 
 int OPERA_TUNER_REQ ; 
 int OPERA_WRITE_MSG ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int usb_control_msg (struct usb_device*,unsigned int,int,int,int,int,int*,int,int) ; 
 unsigned int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opera1_xilinx_rw(struct usb_device *dev, u8 request, u16 value,
			    u8 * data, u16 len, int flags)
{
	int ret;
	u8 tmp;
	u8 *buf;
	unsigned int pipe = (flags == OPERA_READ_MSG) ?
		usb_rcvctrlpipe(dev,0) : usb_sndctrlpipe(dev, 0);
	u8 request_type = (flags == OPERA_READ_MSG) ? USB_DIR_IN : USB_DIR_OUT;

	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	if (flags == OPERA_WRITE_MSG)
		memcpy(buf, data, len);
	ret = usb_control_msg(dev, pipe, request,
			request_type | USB_TYPE_VENDOR, value, 0x0,
			buf, len, 2000);

	if (request == OPERA_TUNER_REQ) {
		tmp = buf[0];
		if (usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			    OPERA_TUNER_REQ, USB_DIR_IN | USB_TYPE_VENDOR,
			    0x01, 0x0, buf, 1, 2000) < 1 || buf[0] != 0x08) {
			ret = 0;
			goto out;
		}
		buf[0] = tmp;
	}
	if (flags == OPERA_READ_MSG)
		memcpy(data, buf, len);
out:
	kfree(buf);
	return ret;
}