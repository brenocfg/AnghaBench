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
struct cx231xx {int state; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int EINVAL ; 
 int ENABLE_FOUR_BYTE ; 
 int ENABLE_ONE_BYTE ; 
 int ENABLE_THREE_BYTE ; 
 int ENABLE_TWE_BYTE ; 
 int ENODEV ; 
 int /*<<< orphan*/  HZ ; 
 int URB_MAX_CTRL_SIZE ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int __usb_control_msg (struct cx231xx*,int,int,int,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_isocdbg (char*,...) ; 
 scalar_t__ reg_debug ; 
 int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx231xx_write_ctrl_reg(struct cx231xx *dev, u8 req, u16 reg, char *buf,
			   int len)
{
	u8 val = 0;
	int ret;
	int pipe = usb_sndctrlpipe(dev->udev, 0);

	if (dev->state & DEV_DISCONNECTED)
		return -ENODEV;

	if ((len < 1) || (len > URB_MAX_CTRL_SIZE))
		return -EINVAL;

	switch (len) {
	case 1:
		val = ENABLE_ONE_BYTE;
		break;
	case 2:
		val = ENABLE_TWE_BYTE;
		break;
	case 3:
		val = ENABLE_THREE_BYTE;
		break;
	case 4:
		val = ENABLE_FOUR_BYTE;
		break;
	default:
		val = 0xFF;	/* invalid option */
	}

	if (val == 0xFF)
		return -EINVAL;

	if (reg_debug) {
		int byte;

		cx231xx_isocdbg("(pipe 0x%08x): OUT: %02x %02x %02x %02x %02x %02x %02x %02x >>>",
			pipe,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			req, 0, val, reg & 0xff,
			reg >> 8, len & 0xff, len >> 8);

		for (byte = 0; byte < len; byte++)
			cx231xx_isocdbg(" %02x", (unsigned char)buf[byte]);
		cx231xx_isocdbg("\n");
	}

	ret = __usb_control_msg(dev, pipe, req,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      val, reg, buf, len, HZ);

	return ret;
}