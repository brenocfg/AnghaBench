#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wacom_features {scalar_t__ oVid; scalar_t__ oPid; scalar_t__ type; int device_type; } ;
struct TYPE_2__ {struct wacom_features features; } ;
struct wacom {TYPE_1__ wacom_wac; } ;
struct hid_device {scalar_t__ vendor; scalar_t__ product; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ HID_ANY_ID ; 
 scalar_t__ HID_GENERIC ; 
 int WACOM_DEVICETYPE_DIRECT ; 
 int WACOM_DEVICETYPE_PEN ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int /*<<< orphan*/  hid_compare_device_paths (struct hid_device*,struct hid_device*,char) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static bool wacom_are_sibling(struct hid_device *hdev,
		struct hid_device *sibling)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_features *features = &wacom->wacom_wac.features;
	struct wacom *sibling_wacom = hid_get_drvdata(sibling);
	struct wacom_features *sibling_features = &sibling_wacom->wacom_wac.features;
	__u32 oVid = features->oVid ? features->oVid : hdev->vendor;
	__u32 oPid = features->oPid ? features->oPid : hdev->product;

	/* The defined oVid/oPid must match that of the sibling */
	if (features->oVid != HID_ANY_ID && sibling->vendor != oVid)
		return false;
	if (features->oPid != HID_ANY_ID && sibling->product != oPid)
		return false;

	/*
	 * Devices with the same VID/PID must share the same physical
	 * device path, while those with different VID/PID must share
	 * the same physical parent device path.
	 */
	if (hdev->vendor == sibling->vendor && hdev->product == sibling->product) {
		if (!hid_compare_device_paths(hdev, sibling, '/'))
			return false;
	} else {
		if (!hid_compare_device_paths(hdev, sibling, '.'))
			return false;
	}

	/* Skip the remaining heuristics unless you are a HID_GENERIC device */
	if (features->type != HID_GENERIC)
		return true;

	/*
	 * Direct-input devices may not be siblings of indirect-input
	 * devices.
	 */
	if ((features->device_type & WACOM_DEVICETYPE_DIRECT) &&
	    !(sibling_features->device_type & WACOM_DEVICETYPE_DIRECT))
		return false;

	/*
	 * Indirect-input devices may not be siblings of direct-input
	 * devices.
	 */
	if (!(features->device_type & WACOM_DEVICETYPE_DIRECT) &&
	    (sibling_features->device_type & WACOM_DEVICETYPE_DIRECT))
		return false;

	/* Pen devices may only be siblings of touch devices */
	if ((features->device_type & WACOM_DEVICETYPE_PEN) &&
	    !(sibling_features->device_type & WACOM_DEVICETYPE_TOUCH))
		return false;

	/* Touch devices may only be siblings of pen devices */
	if ((features->device_type & WACOM_DEVICETYPE_TOUCH) &&
	    !(sibling_features->device_type & WACOM_DEVICETYPE_PEN))
		return false;

	/*
	 * No reason could be found for these two devices to NOT be
	 * siblings, so there's a good chance they ARE siblings
	 */
	return true;
}