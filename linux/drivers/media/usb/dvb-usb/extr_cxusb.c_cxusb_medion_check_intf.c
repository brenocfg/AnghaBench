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
struct usb_interface {int num_altsetting; int /*<<< orphan*/  usb_dev; TYPE_2__* altsetting; } ;
struct TYPE_3__ {int bAlternateSetting; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ cxusb_medion_check_altsetting (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool cxusb_medion_check_intf(struct usb_interface *intf)
{
	unsigned int ctr;

	if (intf->num_altsetting < 2) {
		dev_err(intf->usb_dev, "no alternate interface");

		return false;
	}

	for (ctr = 0; ctr < intf->num_altsetting; ctr++) {
		if (intf->altsetting[ctr].desc.bAlternateSetting != 1)
			continue;

		if (cxusb_medion_check_altsetting(&intf->altsetting[ctr]))
			return true;

		break;
	}

	dev_err(intf->usb_dev, "no iso interface");

	return false;
}