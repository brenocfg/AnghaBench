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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {unsigned char bNumControls; unsigned char bControlSize; int /*<<< orphan*/ * bmControls; int /*<<< orphan*/ * bmControlsType; int /*<<< orphan*/ * guidExtensionCode; } ;
struct uvc_entity {int /*<<< orphan*/  list; int /*<<< orphan*/  name; TYPE_4__ extension; int /*<<< orphan*/ * baSourceID; } ;
struct uvc_device {int /*<<< orphan*/  entities; struct usb_device* udev; TYPE_1__* intf; } ;
struct TYPE_7__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_host_interface {TYPE_3__ desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  idVendor; } ;
struct usb_device {int /*<<< orphan*/  devnum; TYPE_2__ descriptor; } ;
struct TYPE_5__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  UVC_TRACE_DESCR ; 
 int /*<<< orphan*/  UVC_VC_EXTENSION_UNIT ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned char const) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,unsigned char const,int /*<<< orphan*/ ,int) ; 
 struct uvc_entity* uvc_alloc_entity (int /*<<< orphan*/ ,unsigned char const,unsigned int,int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_parse_vendor_control(struct uvc_device *dev,
	const unsigned char *buffer, int buflen)
{
	struct usb_device *udev = dev->udev;
	struct usb_host_interface *alts = dev->intf->cur_altsetting;
	struct uvc_entity *unit;
	unsigned int n, p;
	int handled = 0;

	switch (le16_to_cpu(dev->udev->descriptor.idVendor)) {
	case 0x046d:		/* Logitech */
		if (buffer[1] != 0x41 || buffer[2] != 0x01)
			break;

		/* Logitech implements several vendor specific functions
		 * through vendor specific extension units (LXU).
		 *
		 * The LXU descriptors are similar to XU descriptors
		 * (see "USB Device Video Class for Video Devices", section
		 * 3.7.2.6 "Extension Unit Descriptor") with the following
		 * differences:
		 *
		 * ----------------------------------------------------------
		 * 0		bLength		1	 Number
		 *	Size of this descriptor, in bytes: 24+p+n*2
		 * ----------------------------------------------------------
		 * 23+p+n	bmControlsType	N	Bitmap
		 *	Individual bits in the set are defined:
		 *	0: Absolute
		 *	1: Relative
		 *
		 *	This bitset is mapped exactly the same as bmControls.
		 * ----------------------------------------------------------
		 * 23+p+n*2	bReserved	1	Boolean
		 * ----------------------------------------------------------
		 * 24+p+n*2	iExtension	1	Index
		 *	Index of a string descriptor that describes this
		 *	extension unit.
		 * ----------------------------------------------------------
		 */
		p = buflen >= 22 ? buffer[21] : 0;
		n = buflen >= 25 + p ? buffer[22+p] : 0;

		if (buflen < 25 + p + 2*n) {
			uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
				"interface %d EXTENSION_UNIT error\n",
				udev->devnum, alts->desc.bInterfaceNumber);
			break;
		}

		unit = uvc_alloc_entity(UVC_VC_EXTENSION_UNIT, buffer[3],
					p + 1, 2*n);
		if (unit == NULL)
			return -ENOMEM;

		memcpy(unit->extension.guidExtensionCode, &buffer[4], 16);
		unit->extension.bNumControls = buffer[20];
		memcpy(unit->baSourceID, &buffer[22], p);
		unit->extension.bControlSize = buffer[22+p];
		unit->extension.bmControls = (u8 *)unit + sizeof(*unit);
		unit->extension.bmControlsType = (u8 *)unit + sizeof(*unit)
					       + n;
		memcpy(unit->extension.bmControls, &buffer[23+p], 2*n);

		if (buffer[24+p+2*n] != 0)
			usb_string(udev, buffer[24+p+2*n], unit->name,
				   sizeof(unit->name));
		else
			sprintf(unit->name, "Extension %u", buffer[3]);

		list_add_tail(&unit->list, &dev->entities);
		handled = 1;
		break;
	}

	return handled;
}