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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct us_data {scalar_t__ protocol; char* transport_name; int max_lun; void* transport_reset; int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 scalar_t__ USB_PR_DPCM_USB ; 
 int /*<<< orphan*/  dpcm_transport ; 
 int /*<<< orphan*/  sddr09_host_template ; 
 int /*<<< orphan*/  sddr09_transport ; 
 int sddr09_unusual_dev_list ; 
 struct usb_device_id const* sddr09_usb_ids ; 
 void* usb_stor_CB_reset ; 
 int usb_stor_probe1 (struct us_data**,struct usb_interface*,struct usb_device_id const*,int,int /*<<< orphan*/ *) ; 
 int usb_stor_probe2 (struct us_data*) ; 

__attribute__((used)) static int sddr09_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct us_data *us;
	int result;

	result = usb_stor_probe1(&us, intf, id,
			(id - sddr09_usb_ids) + sddr09_unusual_dev_list,
			&sddr09_host_template);
	if (result)
		return result;

	if (us->protocol == USB_PR_DPCM_USB) {
		us->transport_name = "Control/Bulk-EUSB/SDDR09";
		us->transport = dpcm_transport;
		us->transport_reset = usb_stor_CB_reset;
		us->max_lun = 1;
	} else {
		us->transport_name = "EUSB/SDDR09";
		us->transport = sddr09_transport;
		us->transport_reset = usb_stor_CB_reset;
		us->max_lun = 0;
	}

	result = usb_stor_probe2(us);
	return result;
}