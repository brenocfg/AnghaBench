#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_serial {TYPE_4__* interface; TYPE_2__* dev; } ;
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; int bInterfaceProtocol; } ;
struct TYPE_8__ {TYPE_3__* cur_altsetting; } ;
struct TYPE_7__ {struct usb_interface_descriptor desc; } ;
struct TYPE_5__ {scalar_t__ bDeviceClass; } ;
struct TYPE_6__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ CDC_DEVICE_CLASS ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ LINEO_INTERFACE_CLASS ; 
 scalar_t__ LINEO_INTERFACE_SUBCLASS_SAFESERIAL ; 
#define  LINEO_SAFESERIAL_CRC 129 
#define  LINEO_SAFESERIAL_CRC_PADDED 128 
 int padded ; 

__attribute__((used)) static int safe_startup(struct usb_serial *serial)
{
	struct usb_interface_descriptor	*desc;

	if (serial->dev->descriptor.bDeviceClass != CDC_DEVICE_CLASS)
		return -ENODEV;

	desc = &serial->interface->cur_altsetting->desc;

	if (desc->bInterfaceClass != LINEO_INTERFACE_CLASS)
		return -ENODEV;
	if (desc->bInterfaceSubClass != LINEO_INTERFACE_SUBCLASS_SAFESERIAL)
		return -ENODEV;

	switch (desc->bInterfaceProtocol) {
	case LINEO_SAFESERIAL_CRC:
		break;
	case LINEO_SAFESERIAL_CRC_PADDED:
		padded = true;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}