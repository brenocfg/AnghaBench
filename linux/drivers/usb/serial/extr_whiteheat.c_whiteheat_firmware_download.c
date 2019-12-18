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
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ezusb_fx1_ihex_firmware_download (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int whiteheat_firmware_download(struct usb_serial *serial,
					const struct usb_device_id *id)
{
	int response;

	response = ezusb_fx1_ihex_firmware_download(serial->dev, "whiteheat_loader.fw");
	if (response >= 0) {
		response = ezusb_fx1_ihex_firmware_download(serial->dev, "whiteheat.fw");
		if (response >= 0)
			return 0;
	}
	return -ENOENT;
}