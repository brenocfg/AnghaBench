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
struct input_dev {int dummy; } ;
struct gtco {TYPE_1__* urbinfo; int /*<<< orphan*/  intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gtco* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  interface_to_usbdev (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gtco_input_open(struct input_dev *inputdev)
{
	struct gtco *device = input_get_drvdata(inputdev);

	device->urbinfo->dev = interface_to_usbdev(device->intf);
	if (usb_submit_urb(device->urbinfo, GFP_KERNEL))
		return -EIO;

	return 0;
}