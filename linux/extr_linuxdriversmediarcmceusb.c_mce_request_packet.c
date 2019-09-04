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
struct urb {int dummy; } ;
struct mceusb_dev {int /*<<< orphan*/  pipe_out; int /*<<< orphan*/  usbdev; TYPE_1__* usb_ep_out; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bInterval; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_async_callback ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_xfer_int (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,struct mceusb_dev*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,struct mceusb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_request_packet(struct mceusb_dev *ir, unsigned char *data,
								int size)
{
	int res;
	struct urb *async_urb;
	struct device *dev = ir->dev;
	unsigned char *async_buf;

	async_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (unlikely(!async_urb)) {
		dev_err(dev, "Error, couldn't allocate urb!");
		return;
	}

	async_buf = kmalloc(size, GFP_KERNEL);
	if (!async_buf) {
		usb_free_urb(async_urb);
		return;
	}

	/* outbound data */
	if (usb_endpoint_xfer_int(ir->usb_ep_out))
		usb_fill_int_urb(async_urb, ir->usbdev, ir->pipe_out,
				 async_buf, size, mce_async_callback, ir,
				 ir->usb_ep_out->bInterval);
	else
		usb_fill_bulk_urb(async_urb, ir->usbdev, ir->pipe_out,
				  async_buf, size, mce_async_callback, ir);

	memcpy(async_buf, data, size);

	dev_dbg(dev, "send request called (size=%#x)", size);

	res = usb_submit_urb(async_urb, GFP_ATOMIC);
	if (res) {
		dev_err(dev, "send request FAILED! (res=%d)", res);
		kfree(async_buf);
		usb_free_urb(async_urb);
		return;
	}
	dev_dbg(dev, "send request complete (res=%d)", res);
}