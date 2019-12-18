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
struct usbhid_device {TYPE_2__* intf; } ;
struct hiddev {int exist; int initialized; int /*<<< orphan*/  minor; struct hid_device* hid; int /*<<< orphan*/  existancelock; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; } ;
struct hid_device {unsigned int maxcollection; int quirks; struct hiddev* hiddev; TYPE_1__* collection; struct usbhid_device* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  minor; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HID_COLLECTION_APPLICATION ; 
 int HID_QUIRK_NO_INIT_REPORTS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_INPUT_APPLICATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hiddev_class ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hiddev*) ; 
 struct hiddev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int usb_register_dev (TYPE_2__*,int /*<<< orphan*/ *) ; 

int hiddev_connect(struct hid_device *hid, unsigned int force)
{
	struct hiddev *hiddev;
	struct usbhid_device *usbhid = hid->driver_data;
	int retval;

	if (!force) {
		unsigned int i;
		for (i = 0; i < hid->maxcollection; i++)
			if (hid->collection[i].type ==
			    HID_COLLECTION_APPLICATION &&
			    !IS_INPUT_APPLICATION(hid->collection[i].usage))
				break;

		if (i == hid->maxcollection)
			return -1;
	}

	if (!(hiddev = kzalloc(sizeof(struct hiddev), GFP_KERNEL)))
		return -1;

	init_waitqueue_head(&hiddev->wait);
	INIT_LIST_HEAD(&hiddev->list);
	spin_lock_init(&hiddev->list_lock);
	mutex_init(&hiddev->existancelock);
	hid->hiddev = hiddev;
	hiddev->hid = hid;
	hiddev->exist = 1;
	retval = usb_register_dev(usbhid->intf, &hiddev_class);
	if (retval) {
		hid_err(hid, "Not able to get a minor for this device\n");
		hid->hiddev = NULL;
		kfree(hiddev);
		return -1;
	}

	/*
	 * If HID_QUIRK_NO_INIT_REPORTS is set, make sure we don't initialize
	 * the reports.
	 */
	hiddev->initialized = hid->quirks & HID_QUIRK_NO_INIT_REPORTS;

	hiddev->minor = usbhid->intf->minor;

	return 0;
}