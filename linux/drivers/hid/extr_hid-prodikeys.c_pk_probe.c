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
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct pk_device {unsigned short ifnum; struct pk_device* pm; struct pk_device* pk; struct hid_device* hdev; } ;
struct pcmidi_snd {unsigned short ifnum; struct pcmidi_snd* pm; struct pcmidi_snd* pk; struct hid_device* hdev; } ;
struct hid_device_id {unsigned long driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hid_device {int /*<<< orphan*/  quirks; TYPE_1__ dev; } ;
struct TYPE_5__ {unsigned short bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  HID_QUIRK_NOGET ; 
 unsigned long PK_QUIRK_NOGET ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct pk_device*) ; 
 int /*<<< orphan*/  kfree (struct pk_device*) ; 
 struct pk_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pcmidi_snd_initialise (struct pk_device*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pk_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	unsigned short ifnum = intf->cur_altsetting->desc.bInterfaceNumber;
	unsigned long quirks = id->driver_data;
	struct pk_device *pk;
	struct pcmidi_snd *pm = NULL;

	pk = kzalloc(sizeof(*pk), GFP_KERNEL);
	if (pk == NULL) {
		hid_err(hdev, "can't alloc descriptor\n");
		return -ENOMEM;
	}

	pk->hdev = hdev;

	pm = kzalloc(sizeof(*pm), GFP_KERNEL);
	if (pm == NULL) {
		hid_err(hdev, "can't alloc descriptor\n");
		ret = -ENOMEM;
		goto err_free_pk;
	}

	pm->pk = pk;
	pk->pm = pm;
	pm->ifnum = ifnum;

	hid_set_drvdata(hdev, pk);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "hid parse failed\n");
		goto err_free;
	}

	if (quirks & PK_QUIRK_NOGET) { /* hid_parse cleared all the quirks */
		hdev->quirks |= HID_QUIRK_NOGET;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err_free;
	}

	ret = pcmidi_snd_initialise(pm);
	if (ret < 0)
		goto err_stop;

	return 0;
err_stop:
	hid_hw_stop(hdev);
err_free:
	kfree(pm);
err_free_pk:
	kfree(pk);

	return ret;
}