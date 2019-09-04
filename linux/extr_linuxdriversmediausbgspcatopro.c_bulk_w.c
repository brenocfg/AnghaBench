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
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct gspca_dev {int usb_err; int /*<<< orphan*/ * usb_buf; struct usb_device* dev; } ;

/* Variables and functions */
 int BULK_OUT_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static void bulk_w(struct gspca_dev *gspca_dev,
		  u8 tag,
		  const u8 *data,
		  int length)
{
	struct usb_device *dev = gspca_dev->dev;
	int count, actual_count, ret;

	if (gspca_dev->usb_err < 0)
		return;
	for (;;) {
		count = length > BULK_OUT_SIZE - 1
				? BULK_OUT_SIZE - 1 : length;
		gspca_dev->usb_buf[0] = tag;
		memcpy(&gspca_dev->usb_buf[1], data, count);
		ret = usb_bulk_msg(dev,
				   usb_sndbulkpipe(dev, 3),
				   gspca_dev->usb_buf, count + 1,
				   &actual_count, 500);
		if (ret < 0) {
			pr_err("bulk write error %d tag=%02x\n",
				ret, tag);
			gspca_dev->usb_err = ret;
			return;
		}
		length -= count;
		if (length <= 0)
			break;
		data += count;
	}
}