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
struct bcm5974_config {scalar_t__ tp_type; int um_size; size_t um_switch_idx; char um_switch_on; char um_switch_off; int /*<<< orphan*/  um_req_idx; int /*<<< orphan*/  um_req_val; } ;
struct bcm5974 {TYPE_1__* intf; int /*<<< orphan*/  udev; struct bcm5974_config cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM5974_WELLSPRING_MODE_READ_REQUEST_ID ; 
 int /*<<< orphan*/  BCM5974_WELLSPRING_MODE_WRITE_REQUEST_ID ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TYPE3 ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dprintk (int,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm5974_wellspring_mode(struct bcm5974 *dev, bool on)
{
	const struct bcm5974_config *c = &dev->cfg;
	int retval = 0, size;
	char *data;

	/* Type 3 does not require a mode switch */
	if (c->tp_type == TYPE3)
		return 0;

	data = kmalloc(c->um_size, GFP_KERNEL);
	if (!data) {
		dev_err(&dev->intf->dev, "out of memory\n");
		retval = -ENOMEM;
		goto out;
	}

	/* read configuration */
	size = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
			BCM5974_WELLSPRING_MODE_READ_REQUEST_ID,
			USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			c->um_req_val, c->um_req_idx, data, c->um_size, 5000);

	if (size != c->um_size) {
		dev_err(&dev->intf->dev, "could not read from device\n");
		retval = -EIO;
		goto out;
	}

	/* apply the mode switch */
	data[c->um_switch_idx] = on ? c->um_switch_on : c->um_switch_off;

	/* write configuration */
	size = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			BCM5974_WELLSPRING_MODE_WRITE_REQUEST_ID,
			USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			c->um_req_val, c->um_req_idx, data, c->um_size, 5000);

	if (size != c->um_size) {
		dev_err(&dev->intf->dev, "could not write to device\n");
		retval = -EIO;
		goto out;
	}

	dprintk(2, "bcm5974: switched to %s mode.\n",
		on ? "wellspring" : "normal");

 out:
	kfree(data);
	return retval;
}