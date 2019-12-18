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
struct gspca_dev {int usb_err; int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reg_w(struct gspca_dev *gspca_dev,
		 int len)
{
	int alen, ret;

	if (gspca_dev->usb_err < 0)
		return;

	ret = usb_bulk_msg(gspca_dev->dev,
			usb_sndbulkpipe(gspca_dev->dev, 4),
			gspca_dev->usb_buf,
			len,
			&alen,
			500);	/* timeout in milliseconds */
	if (ret < 0) {
		pr_err("reg write [%02x] error %d\n",
		       gspca_dev->usb_buf[0], ret);
		gspca_dev->usb_err = ret;
	}
}