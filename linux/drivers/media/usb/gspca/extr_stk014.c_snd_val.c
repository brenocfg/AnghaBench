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
struct gspca_dev {int usb_err; unsigned int* usb_buf; struct usb_device* dev; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,unsigned int*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static void snd_val(struct gspca_dev *gspca_dev,
			int ads,
			unsigned int val)
{
	struct usb_device *dev = gspca_dev->dev;
	int alen, ret;
	__u8 seq = 0;

	if (ads == 0x003f08) {
		reg_r(gspca_dev, 0x0704);
		seq = reg_r(gspca_dev, 0x0705);
		reg_r(gspca_dev, 0x0650);
		reg_w(gspca_dev, 0x654, seq);
	} else {
		reg_w(gspca_dev, 0x654, (ads >> 16) & 0xff);
	}
	reg_w(gspca_dev, 0x655, (ads >> 8) & 0xff);
	reg_w(gspca_dev, 0x656, ads & 0xff);
	reg_w(gspca_dev, 0x657, 0);
	reg_w(gspca_dev, 0x658, 0x04);	/* size */
	reg_w(gspca_dev, 0x659, 0);
	reg_w(gspca_dev, 0x65a, 0);
	reg_w(gspca_dev, 0x65b, 0);
	reg_w(gspca_dev, 0x650, 5);
	if (gspca_dev->usb_err < 0)
		return;
	gspca_dev->usb_buf[0] = val >> 24;
	gspca_dev->usb_buf[1] = val >> 16;
	gspca_dev->usb_buf[2] = val >> 8;
	gspca_dev->usb_buf[3] = val;
	ret = usb_bulk_msg(dev,
			usb_sndbulkpipe(dev, 6),
			gspca_dev->usb_buf,
			4,
			&alen,
			500);	/* timeout in milliseconds */
	if (ret < 0) {
		pr_err("snd_val err %d\n", ret);
		gspca_dev->usb_err = ret;
	} else {
		if (ads == 0x003f08) {
			seq += 4;
			seq &= 0x3f;
			reg_w(gspca_dev, 0x705, seq);
		}
	}
}