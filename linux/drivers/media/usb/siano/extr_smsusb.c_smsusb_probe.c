#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int num_altsetting; TYPE_6__* cur_altsetting; } ;
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct usb_device {char* devpath; TYPE_7__* bus; TYPE_4__* actconfig; } ;
typedef  int /*<<< orphan*/  devpath ;
struct TYPE_16__ {scalar_t__ intf_num; } ;
struct TYPE_15__ {int busnum; } ;
struct TYPE_13__ {scalar_t__ bInterfaceNumber; int bNumEndpoints; } ;
struct TYPE_14__ {TYPE_5__ desc; TYPE_2__* endpoint; } ;
struct TYPE_11__ {int bNumInterfaces; } ;
struct TYPE_12__ {TYPE_3__ desc; } ;
struct TYPE_9__ {int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bmAttributes; } ;
struct TYPE_10__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SMS1XXX_BOARD_SIANO_STELLAR_ROM ; 
 int USB_DIR_IN ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  sms_board_load_modules (int /*<<< orphan*/ ) ; 
 TYPE_8__* sms_get_board (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_registry_getmode (char*) ; 
 int smsusb1_load_firmware (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smsusb_init_device (struct usb_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 int usb_clear_halt (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int usb_set_interface (struct usb_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int smsusb_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	char devpath[32];
	int i, rc;

	pr_info("board id=%lu, interface number %d\n",
		 id->driver_info,
		 intf->cur_altsetting->desc.bInterfaceNumber);

	if (sms_get_board(id->driver_info)->intf_num !=
	    intf->cur_altsetting->desc.bInterfaceNumber) {
		pr_debug("interface %d won't be used. Expecting interface %d to popup\n",
			intf->cur_altsetting->desc.bInterfaceNumber,
			sms_get_board(id->driver_info)->intf_num);
		return -ENODEV;
	}

	if (intf->num_altsetting > 1) {
		rc = usb_set_interface(udev,
				       intf->cur_altsetting->desc.bInterfaceNumber,
				       0);
		if (rc < 0) {
			pr_err("usb_set_interface failed, rc %d\n", rc);
			return rc;
		}
	}

	pr_debug("smsusb_probe %d\n",
	       intf->cur_altsetting->desc.bInterfaceNumber);
	for (i = 0; i < intf->cur_altsetting->desc.bNumEndpoints; i++) {
		pr_debug("endpoint %d %02x %02x %d\n", i,
		       intf->cur_altsetting->endpoint[i].desc.bEndpointAddress,
		       intf->cur_altsetting->endpoint[i].desc.bmAttributes,
		       intf->cur_altsetting->endpoint[i].desc.wMaxPacketSize);
		if (intf->cur_altsetting->endpoint[i].desc.bEndpointAddress &
		    USB_DIR_IN)
			rc = usb_clear_halt(udev, usb_rcvbulkpipe(udev,
				intf->cur_altsetting->endpoint[i].desc.bEndpointAddress));
		else
			rc = usb_clear_halt(udev, usb_sndbulkpipe(udev,
				intf->cur_altsetting->endpoint[i].desc.bEndpointAddress));
	}
	if ((udev->actconfig->desc.bNumInterfaces == 2) &&
	    (intf->cur_altsetting->desc.bInterfaceNumber == 0)) {
		pr_debug("rom interface 0 is not used\n");
		return -ENODEV;
	}

	if (id->driver_info == SMS1XXX_BOARD_SIANO_STELLAR_ROM) {
		/* Detected a Siano Stellar uninitialized */

		snprintf(devpath, sizeof(devpath), "usb\\%d-%s",
			 udev->bus->busnum, udev->devpath);
		pr_info("stellar device in cold state was found at %s.\n",
			devpath);
		rc = smsusb1_load_firmware(
				udev, smscore_registry_getmode(devpath),
				id->driver_info);

		/* This device will reset and gain another USB ID */
		if (!rc)
			pr_info("stellar device now in warm state\n");
		else
			pr_err("Failed to put stellar in warm state. Error: %d\n",
			       rc);

		return rc;
	} else {
		rc = smsusb_init_device(intf, id->driver_info);
	}

	pr_info("Device initialized with return code %d\n", rc);
	sms_board_load_modules(id->driver_info);
	return rc;
}