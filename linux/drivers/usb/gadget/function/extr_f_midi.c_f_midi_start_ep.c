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
struct usb_function {TYPE_1__* config; } ;
struct usb_ep {struct f_midi* driver_data; int /*<<< orphan*/  name; } ;
struct usb_composite_dev {int dummy; } ;
struct f_midi {int /*<<< orphan*/  gadget; } ;
struct TYPE_2__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct usb_composite_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int config_ep_by_speed (int /*<<< orphan*/ ,struct usb_function*,struct usb_ep*) ; 
 int /*<<< orphan*/  usb_ep_disable (struct usb_ep*) ; 
 int usb_ep_enable (struct usb_ep*) ; 

__attribute__((used)) static int f_midi_start_ep(struct f_midi *midi,
			   struct usb_function *f,
			   struct usb_ep *ep)
{
	int err;
	struct usb_composite_dev *cdev = f->config->cdev;

	usb_ep_disable(ep);

	err = config_ep_by_speed(midi->gadget, f, ep);
	if (err) {
		ERROR(cdev, "can't configure %s: %d\n", ep->name, err);
		return err;
	}

	err = usb_ep_enable(ep);
	if (err) {
		ERROR(cdev, "can't start %s: %d\n", ep->name, err);
		return err;
	}

	ep->driver_data = midi;

	return 0;
}