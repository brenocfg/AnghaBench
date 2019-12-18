#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {char* name; int* evbit; TYPE_1__ dev; int /*<<< orphan*/  id; scalar_t__ keycodemax; scalar_t__ keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  phys; } ;
struct em28xx {struct input_dev* sbutton_input_dev; TYPE_2__* intf; int /*<<< orphan*/  snapshot_button_path; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM28XX_SNAPSHOT_KEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 struct usb_device* interface_to_usbdev (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_register_snapshot_button(struct em28xx *dev)
{
	struct usb_device *udev = interface_to_usbdev(dev->intf);
	struct input_dev *input_dev;
	int err;

	dev_info(&dev->intf->dev, "Registering snapshot button...\n");
	input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	usb_make_path(udev, dev->snapshot_button_path,
		      sizeof(dev->snapshot_button_path));
	strlcat(dev->snapshot_button_path, "/sbutton",
		sizeof(dev->snapshot_button_path));

	input_dev->name = "em28xx snapshot button";
	input_dev->phys = dev->snapshot_button_path;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	set_bit(EM28XX_SNAPSHOT_KEY, input_dev->keybit);
	input_dev->keycodesize = 0;
	input_dev->keycodemax = 0;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &dev->intf->dev;

	err = input_register_device(input_dev);
	if (err) {
		dev_err(&dev->intf->dev, "input_register_device failed\n");
		input_free_device(input_dev);
		return err;
	}

	dev->sbutton_input_dev = input_dev;
	return 0;
}