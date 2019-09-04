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
struct i2c_diolan_u2c {TYPE_1__* interface; int /*<<< orphan*/  ibuffer; int /*<<< orphan*/  ep_in; int /*<<< orphan*/  usb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOLAN_USB_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diolan_flush_input(struct i2c_diolan_u2c *dev)
{
	int i;

	for (i = 0; i < 10; i++) {
		int actual = 0;
		int ret;

		ret = usb_bulk_msg(dev->usb_dev,
				   usb_rcvbulkpipe(dev->usb_dev, dev->ep_in),
				   dev->ibuffer, sizeof(dev->ibuffer), &actual,
				   DIOLAN_USB_TIMEOUT);
		if (ret < 0 || actual == 0)
			break;
	}
	if (i == 10)
		dev_err(&dev->interface->dev, "Failed to flush input buffer\n");
}