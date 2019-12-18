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
struct usbtmc_device_data {scalar_t__ iin_urb; scalar_t__ iin_ep_present; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct usbtmc_device_data* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtmc_resume(struct usb_interface *intf)
{
	struct usbtmc_device_data *data = usb_get_intfdata(intf);
	int retcode = 0;

	if (data->iin_ep_present && data->iin_urb)
		retcode = usb_submit_urb(data->iin_urb, GFP_KERNEL);
	if (retcode)
		dev_err(&intf->dev, "Failed to submit iin_urb\n");

	return retcode;
}