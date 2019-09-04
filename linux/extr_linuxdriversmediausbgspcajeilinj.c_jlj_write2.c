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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void jlj_write2(struct gspca_dev *gspca_dev, unsigned char *command)
{
	int retval;

	if (gspca_dev->usb_err < 0)
		return;
	memcpy(gspca_dev->usb_buf, command, 2);
	retval = usb_bulk_msg(gspca_dev->dev,
			usb_sndbulkpipe(gspca_dev->dev, 3),
			gspca_dev->usb_buf, 2, NULL, 500);
	if (retval < 0) {
		pr_err("command write [%02x] error %d\n",
		       gspca_dev->usb_buf[0], retval);
		gspca_dev->usb_err = retval;
	}
}