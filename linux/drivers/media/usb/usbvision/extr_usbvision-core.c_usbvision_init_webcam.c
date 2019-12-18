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
struct usb_usbvision {unsigned char* ctrl_urb_buffer; size_t dev_model; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  init_values ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {scalar_t__ video_norm; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int USBVISION_CLK_OUT ; 
 int USBVISION_DAT_IO ; 
 int /*<<< orphan*/  USBVISION_IOPIN_REG ; 
 int USBVISION_IO_2 ; 
 int /*<<< orphan*/  USBVISION_OP_CODE ; 
 int /*<<< orphan*/  USBVISION_SER_CONT ; 
 scalar_t__ USBVISION_SER_DAT1 ; 
 int /*<<< orphan*/  USBVISION_SER_MODE ; 
 int USBVISION_SER_MODE_SIO ; 
 int USBVISION_SER_MODE_SOFT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_VENDOR ; 
 scalar_t__ V4L2_STD_NTSC ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* usbvision_device_data ; 
 int /*<<< orphan*/  usbvision_write_reg (struct usb_usbvision*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbvision_init_webcam(struct usb_usbvision *usbvision)
{
	int rc;
	int i;
	static char init_values[38][3] = {
		{ 0x04, 0x12, 0x08 }, { 0x05, 0xff, 0xc8 }, { 0x06, 0x18, 0x07 }, { 0x07, 0x90, 0x00 },
		{ 0x09, 0x00, 0x00 }, { 0x0a, 0x00, 0x00 }, { 0x0b, 0x08, 0x00 }, { 0x0d, 0xcc, 0xcc },
		{ 0x0e, 0x13, 0x14 }, { 0x10, 0x9b, 0x83 }, { 0x11, 0x5a, 0x3f }, { 0x12, 0xe4, 0x73 },
		{ 0x13, 0x88, 0x84 }, { 0x14, 0x89, 0x80 }, { 0x15, 0x00, 0x20 }, { 0x16, 0x00, 0x00 },
		{ 0x17, 0xff, 0xa0 }, { 0x18, 0x6b, 0x20 }, { 0x19, 0x22, 0x40 }, { 0x1a, 0x10, 0x07 },
		{ 0x1b, 0x00, 0x47 }, { 0x1c, 0x03, 0xe0 }, { 0x1d, 0x00, 0x00 }, { 0x1e, 0x00, 0x00 },
		{ 0x1f, 0x00, 0x00 }, { 0x20, 0x00, 0x00 }, { 0x21, 0x00, 0x00 }, { 0x22, 0x00, 0x00 },
		{ 0x23, 0x00, 0x00 }, { 0x24, 0x00, 0x00 }, { 0x25, 0x00, 0x00 }, { 0x26, 0x00, 0x00 },
		{ 0x27, 0x00, 0x00 }, { 0x28, 0x00, 0x00 }, { 0x29, 0x00, 0x00 }, { 0x08, 0x80, 0x60 },
		{ 0x0f, 0x2d, 0x24 }, { 0x0c, 0x80, 0x80 }
	};
	unsigned char *value = usbvision->ctrl_urb_buffer;

	/* the only difference between PAL and NTSC init_values */
	if (usbvision_device_data[usbvision->dev_model].video_norm == V4L2_STD_NTSC)
		init_values[4][1] = 0x34;

	for (i = 0; i < sizeof(init_values) / 3; i++) {
		usbvision_write_reg(usbvision, USBVISION_SER_MODE, USBVISION_SER_MODE_SOFT);
		memcpy(value, init_values[i], 3);
		rc = usb_control_msg(usbvision->dev,
				     usb_sndctrlpipe(usbvision->dev, 1),
				     USBVISION_OP_CODE,
				     USB_DIR_OUT | USB_TYPE_VENDOR |
				     USB_RECIP_ENDPOINT, 0,
				     (__u16) USBVISION_SER_DAT1, value,
				     3, HZ);
		if (rc < 0)
			return rc;
		usbvision_write_reg(usbvision, USBVISION_SER_MODE, USBVISION_SER_MODE_SIO);
		/* write 3 bytes to the serial port using SIO mode */
		usbvision_write_reg(usbvision, USBVISION_SER_CONT, 3 | 0x10);
		usbvision_write_reg(usbvision, USBVISION_IOPIN_REG, 0);
		usbvision_write_reg(usbvision, USBVISION_SER_MODE, USBVISION_SER_MODE_SOFT);
		usbvision_write_reg(usbvision, USBVISION_IOPIN_REG, USBVISION_IO_2);
		usbvision_write_reg(usbvision, USBVISION_SER_MODE, USBVISION_SER_MODE_SOFT | USBVISION_CLK_OUT);
		usbvision_write_reg(usbvision, USBVISION_SER_MODE, USBVISION_SER_MODE_SOFT | USBVISION_DAT_IO);
		usbvision_write_reg(usbvision, USBVISION_SER_MODE, USBVISION_SER_MODE_SOFT | USBVISION_CLK_OUT | USBVISION_DAT_IO);
	}

	return 0;
}