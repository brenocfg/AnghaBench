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
struct wacom_features {scalar_t__ pktlen; scalar_t__ type; int device_type; int quirks; } ;
struct wacom_wac {struct wacom_features features; } ;
struct wacom {int resources; int /*<<< orphan*/  init_work; struct wacom_wac wacom_wac; struct hid_device* hdev; } ;
struct hid_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BAMBOO_PAD ; 
 scalar_t__ BAMBOO_PEN ; 
 scalar_t__ BAMBOO_TOUCH ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HID_CONNECT_DRIVER ; 
 unsigned int HID_CONNECT_HIDRAW ; 
 scalar_t__ HID_GENERIC ; 
 int WACOM_DEVICETYPE_NONE ; 
 int WACOM_DEVICETYPE_PAD ; 
 int WACOM_DEVICETYPE_PEN ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int WACOM_DEVICETYPE_WL_MONITOR ; 
 scalar_t__ WACOM_PKGLEN_BPAD_TOUCH ; 
 scalar_t__ WACOM_PKGLEN_BPAD_TOUCH_USB ; 
 scalar_t__ WACOM_PKGLEN_MAX ; 
 scalar_t__ WACOM_PKGLEN_PENABLED ; 
 int WACOM_QUIRK_BATTERY ; 
 scalar_t__ WIRELESS ; 
 int /*<<< orphan*/  _wacom_query_tablet_data (struct wacom*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devres_close_group (int /*<<< orphan*/ *,struct wacom*) ; 
 int /*<<< orphan*/  devres_open_group (int /*<<< orphan*/ *,struct wacom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_open (struct hid_device*) ; 
 int hid_hw_start (struct hid_device*,unsigned int) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int wacom_add_shared_data (struct hid_device*) ; 
 int wacom_allocate_inputs (struct wacom*) ; 
 int /*<<< orphan*/  wacom_calculate_res (struct wacom_features*) ; 
 scalar_t__ wacom_compute_pktlen (struct hid_device*) ; 
 int wacom_initialize_battery (struct wacom*) ; 
 int wacom_initialize_leds (struct wacom*) ; 
 int wacom_initialize_remotes (struct wacom*) ; 
 int /*<<< orphan*/  wacom_query_tablet_data (struct wacom*) ; 
 int wacom_register_inputs (struct wacom*) ; 
 int /*<<< orphan*/  wacom_release_resources (struct wacom*) ; 
 int /*<<< orphan*/  wacom_retrieve_hid_descriptor (struct hid_device*,struct wacom_features*) ; 
 int /*<<< orphan*/  wacom_set_default_phy (struct wacom_features*) ; 
 int /*<<< orphan*/  wacom_set_shared_values (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_setup_device_quirks (struct wacom*) ; 
 int /*<<< orphan*/  wacom_update_name (struct wacom*,char*) ; 

__attribute__((used)) static int wacom_parse_and_register(struct wacom *wacom, bool wireless)
{
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;
	struct hid_device *hdev = wacom->hdev;
	int error;
	unsigned int connect_mask = HID_CONNECT_HIDRAW;

	features->pktlen = wacom_compute_pktlen(hdev);
	if (features->pktlen > WACOM_PKGLEN_MAX)
		return -EINVAL;

	if (!devres_open_group(&hdev->dev, wacom, GFP_KERNEL))
		return -ENOMEM;

	wacom->resources = true;

	error = wacom_allocate_inputs(wacom);
	if (error)
		goto fail;

	/*
	 * Bamboo Pad has a generic hid handling for the Pen, and we switch it
	 * into debug mode for the touch part.
	 * We ignore the other interfaces.
	 */
	if (features->type == BAMBOO_PAD) {
		if (features->pktlen == WACOM_PKGLEN_PENABLED) {
			features->type = HID_GENERIC;
		} else if ((features->pktlen != WACOM_PKGLEN_BPAD_TOUCH) &&
			   (features->pktlen != WACOM_PKGLEN_BPAD_TOUCH_USB)) {
			error = -ENODEV;
			goto fail;
		}
	}

	/* set the default size in case we do not get them from hid */
	wacom_set_default_phy(features);

	/* Retrieve the physical and logical size for touch devices */
	wacom_retrieve_hid_descriptor(hdev, features);
	wacom_setup_device_quirks(wacom);

	if (features->device_type == WACOM_DEVICETYPE_NONE &&
	    features->type != WIRELESS) {
		error = features->type == HID_GENERIC ? -ENODEV : 0;

		dev_warn(&hdev->dev, "Unknown device_type for '%s'. %s.",
			 hdev->name,
			 error ? "Ignoring" : "Assuming pen");

		if (error)
			goto fail;

		features->device_type |= WACOM_DEVICETYPE_PEN;
	}

	wacom_calculate_res(features);

	wacom_update_name(wacom, wireless ? " (WL)" : "");

	/* pen only Bamboo neither support touch nor pad */
	if ((features->type == BAMBOO_PEN) &&
	    ((features->device_type & WACOM_DEVICETYPE_TOUCH) ||
	    (features->device_type & WACOM_DEVICETYPE_PAD))) {
		error = -ENODEV;
		goto fail;
	}

	error = wacom_add_shared_data(hdev);
	if (error)
		goto fail;

	if (!(features->device_type & WACOM_DEVICETYPE_WL_MONITOR) &&
	     (features->quirks & WACOM_QUIRK_BATTERY)) {
		error = wacom_initialize_battery(wacom);
		if (error)
			goto fail;
	}

	error = wacom_register_inputs(wacom);
	if (error)
		goto fail;

	if (wacom->wacom_wac.features.device_type & WACOM_DEVICETYPE_PAD) {
		error = wacom_initialize_leds(wacom);
		if (error)
			goto fail;

		error = wacom_initialize_remotes(wacom);
		if (error)
			goto fail;
	}

	if (features->type == HID_GENERIC)
		connect_mask |= HID_CONNECT_DRIVER;

	/* Regular HID work starts now */
	error = hid_hw_start(hdev, connect_mask);
	if (error) {
		hid_err(hdev, "hw start failed\n");
		goto fail;
	}

	if (!wireless) {
		/* Note that if query fails it is not a hard failure */
		wacom_query_tablet_data(wacom);
	}

	/* touch only Bamboo doesn't support pen */
	if ((features->type == BAMBOO_TOUCH) &&
	    (features->device_type & WACOM_DEVICETYPE_PEN)) {
		cancel_delayed_work_sync(&wacom->init_work);
		_wacom_query_tablet_data(wacom);
		error = -ENODEV;
		goto fail_quirks;
	}

	if (features->device_type & WACOM_DEVICETYPE_WL_MONITOR)
		error = hid_hw_open(hdev);

	wacom_set_shared_values(wacom_wac);
	devres_close_group(&hdev->dev, wacom);

	return 0;

fail_quirks:
	hid_hw_stop(hdev);
fail:
	wacom_release_resources(wacom);
	return error;
}