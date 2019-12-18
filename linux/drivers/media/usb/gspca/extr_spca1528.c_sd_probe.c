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
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct sd {int dummy; } ;
struct TYPE_3__ {int bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int gspca_dev_probe2 (struct usb_interface*,struct usb_device_id const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_desc ; 

__attribute__((used)) static int sd_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	/* the video interface for isochronous transfer is 1 */
	if (intf->cur_altsetting->desc.bInterfaceNumber != 1)
		return -ENODEV;

	return gspca_dev_probe2(intf, id, &sd_desc, sizeof(struct sd),
				THIS_MODULE);
}