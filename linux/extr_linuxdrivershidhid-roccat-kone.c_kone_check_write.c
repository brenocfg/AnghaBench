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
typedef  int uint8_t ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kone_command_confirm_write ; 
 int kone_receive (struct usb_device*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int kone_check_write(struct usb_device *usb_dev)
{
	int retval;
	uint8_t data;

	do {
		/*
		 * Mouse needs 50 msecs until it says ok, but there are
		 * 30 more msecs needed for next write to work.
		 */
		msleep(80);

		retval = kone_receive(usb_dev,
				kone_command_confirm_write, &data, 1);
		if (retval)
			return retval;

		/*
		 * value of 3 seems to mean something like
		 * "not finished yet, but it looks good"
		 * So check again after a moment.
		 */
	} while (data == 3);

	if (data == 1) /* everything alright */
		return 0;

	/* unknown answer */
	dev_err(&usb_dev->dev, "got retval %d when checking write\n", data);
	return -EIO;
}