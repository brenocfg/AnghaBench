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
struct usb_device {int dummy; } ;
struct gspca_dev {int usb_err; int /*<<< orphan*/  usb_buf; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static void rcv_val(struct gspca_dev *gspca_dev,
			int ads)
{
	struct usb_device *dev = gspca_dev->dev;
	int alen, ret;

	reg_w(gspca_dev, 0x634, (ads >> 16) & 0xff);
	reg_w(gspca_dev, 0x635, (ads >> 8) & 0xff);
	reg_w(gspca_dev, 0x636, ads & 0xff);
	reg_w(gspca_dev, 0x637, 0);
	reg_w(gspca_dev, 0x638, 4);	/* len & 0xff */
	reg_w(gspca_dev, 0x639, 0);	/* len >> 8 */
	reg_w(gspca_dev, 0x63a, 0);
	reg_w(gspca_dev, 0x63b, 0);
	reg_w(gspca_dev, 0x630, 5);
	if (gspca_dev->usb_err < 0)
		return;
	ret = usb_bulk_msg(dev,
			usb_rcvbulkpipe(dev, 0x05),
			gspca_dev->usb_buf,
			4,		/* length */
			&alen,
			500);		/* timeout in milliseconds */
	if (ret < 0) {
		pr_err("rcv_val err %d\n", ret);
		gspca_dev->usb_err = ret;
	}
}