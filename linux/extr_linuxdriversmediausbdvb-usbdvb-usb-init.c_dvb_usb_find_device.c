#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_3__ descriptor; } ;
struct dvb_usb_device_properties {int num_device_descs; int /*<<< orphan*/  (* identify_state ) (struct usb_device*,struct dvb_usb_device_properties*,struct dvb_usb_device_description**,int*) ;struct dvb_usb_device_description* devices; } ;
struct dvb_usb_device_description {TYPE_2__** warm_ids; TYPE_1__** cold_ids; } ;
struct TYPE_5__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct TYPE_4__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;

/* Variables and functions */
 int DVB_USB_ID_MAX_NUM ; 
 int /*<<< orphan*/  deb_info (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_device*,struct dvb_usb_device_properties*,struct dvb_usb_device_description**,int*) ; 

__attribute__((used)) static struct dvb_usb_device_description *dvb_usb_find_device(struct usb_device *udev, struct dvb_usb_device_properties *props, int *cold)
{
	int i, j;
	struct dvb_usb_device_description *desc = NULL;

	*cold = -1;

	for (i = 0; i < props->num_device_descs; i++) {

		for (j = 0; j < DVB_USB_ID_MAX_NUM && props->devices[i].cold_ids[j] != NULL; j++) {
			deb_info("check for cold %x %x\n", props->devices[i].cold_ids[j]->idVendor, props->devices[i].cold_ids[j]->idProduct);
			if (props->devices[i].cold_ids[j]->idVendor  == le16_to_cpu(udev->descriptor.idVendor) &&
				props->devices[i].cold_ids[j]->idProduct == le16_to_cpu(udev->descriptor.idProduct)) {
				*cold = 1;
				desc = &props->devices[i];
				break;
			}
		}

		if (desc != NULL)
			break;

		for (j = 0; j < DVB_USB_ID_MAX_NUM && props->devices[i].warm_ids[j] != NULL; j++) {
			deb_info("check for warm %x %x\n", props->devices[i].warm_ids[j]->idVendor, props->devices[i].warm_ids[j]->idProduct);
			if (props->devices[i].warm_ids[j]->idVendor == le16_to_cpu(udev->descriptor.idVendor) &&
				props->devices[i].warm_ids[j]->idProduct == le16_to_cpu(udev->descriptor.idProduct)) {
				*cold = 0;
				desc = &props->devices[i];
				break;
			}
		}
	}

	if (desc != NULL && props->identify_state != NULL)
		props->identify_state(udev, props, &desc, cold);

	return desc;
}