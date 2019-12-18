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
struct usb_fpix {int /*<<< orphan*/  work_struct; } ;
struct gspca_dev {TYPE_1__** urb; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPIX_MAX_TRANSFER ; 
 int /*<<< orphan*/  FPIX_TIMEOUT ; 
 int command (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct usb_fpix *dev = (struct usb_fpix *) gspca_dev;
	int ret, len;

	/* Init the device */
	ret = command(gspca_dev, 0);
	if (ret < 0) {
		pr_err("init failed %d\n", ret);
		return ret;
	}

	/* Read the result of the command. Ignore the result, for it
	 * varies with the device. */
	ret = usb_bulk_msg(gspca_dev->dev,
			gspca_dev->urb[0]->pipe,
			gspca_dev->urb[0]->transfer_buffer,
			FPIX_MAX_TRANSFER, &len,
			FPIX_TIMEOUT);
	if (ret < 0) {
		pr_err("usb_bulk_msg failed %d\n", ret);
		return ret;
	}

	/* Request a frame, but don't read it */
	ret = command(gspca_dev, 1);
	if (ret < 0) {
		pr_err("frame request failed %d\n", ret);
		return ret;
	}

	/* Again, reset bulk in endpoint */
	usb_clear_halt(gspca_dev->dev, gspca_dev->urb[0]->pipe);

	schedule_work(&dev->work_struct);

	return 0;
}