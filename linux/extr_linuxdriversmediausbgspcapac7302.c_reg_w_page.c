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
typedef  scalar_t__ u8 ;
struct gspca_dev {int usb_err; scalar_t__* usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ const SKIP ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  pr_err (char*,int,scalar_t__ const,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reg_w_page(struct gspca_dev *gspca_dev,
			const u8 *page, int len)
{
	int index;
	int ret = 0;

	if (gspca_dev->usb_err < 0)
		return;
	for (index = 0; index < len; index++) {
		if (page[index] == SKIP)		/* skip this index */
			continue;
		gspca_dev->usb_buf[0] = page[index];
		ret = usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,			/* request */
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0, index, gspca_dev->usb_buf, 1,
				500);
		if (ret < 0) {
			pr_err("reg_w_page() failed i: %02x v: %02x error %d\n",
			       index, page[index], ret);
			gspca_dev->usb_err = ret;
			break;
		}
	}
}