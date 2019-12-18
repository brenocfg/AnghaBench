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
struct wacom_features {scalar_t__ type; int device_type; } ;
struct wacom_wac {int mode_report; int mode_value; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; struct hid_device* hdev; } ;
struct hid_device {scalar_t__ bus; } ;

/* Variables and functions */
 scalar_t__ BAMBOO_PAD ; 
 scalar_t__ BAMBOO_PT ; 
 scalar_t__ BUS_BLUETOOTH ; 
 scalar_t__ HID_GENERIC ; 
 scalar_t__ TABLETPC ; 
 scalar_t__ WACOM_24HDT ; 
 scalar_t__ WACOM_27QHDT ; 
 int WACOM_DEVICETYPE_PEN ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int wacom_bt_query_tablet_data (struct hid_device*,int,struct wacom_features*) ; 
 int wacom_hid_set_device_mode (struct hid_device*) ; 
 int /*<<< orphan*/  wacom_set_device_mode (struct hid_device*,struct wacom_wac*) ; 

__attribute__((used)) static int _wacom_query_tablet_data(struct wacom *wacom)
{
	struct hid_device *hdev = wacom->hdev;
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;

	if (hdev->bus == BUS_BLUETOOTH)
		return wacom_bt_query_tablet_data(hdev, 1, features);

	if (features->type != HID_GENERIC) {
		if (features->device_type & WACOM_DEVICETYPE_TOUCH) {
			if (features->type > TABLETPC) {
				/* MT Tablet PC touch */
				wacom_wac->mode_report = 3;
				wacom_wac->mode_value = 4;
			} else if (features->type == WACOM_24HDT) {
				wacom_wac->mode_report = 18;
				wacom_wac->mode_value = 2;
			} else if (features->type == WACOM_27QHDT) {
				wacom_wac->mode_report = 131;
				wacom_wac->mode_value = 2;
			} else if (features->type == BAMBOO_PAD) {
				wacom_wac->mode_report = 2;
				wacom_wac->mode_value = 2;
			}
		} else if (features->device_type & WACOM_DEVICETYPE_PEN) {
			if (features->type <= BAMBOO_PT) {
				wacom_wac->mode_report = 2;
				wacom_wac->mode_value = 2;
			}
		}
	}

	wacom_set_device_mode(hdev, wacom_wac);

	if (features->type == HID_GENERIC)
		return wacom_hid_set_device_mode(hdev);

	return 0;
}