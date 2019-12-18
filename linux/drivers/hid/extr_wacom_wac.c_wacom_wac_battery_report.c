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
struct TYPE_2__ {int bat_status; int battery_capacity; int bat_charging; int bat_connected; int ps_connected; } ;
struct wacom_features {int quirks; } ;
struct wacom_wac {TYPE_1__ hid_data; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int WACOM_QUIRK_BATTERY ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  wacom_notify_battery (struct wacom_wac*,int,int,int,int,int) ; 

__attribute__((used)) static void wacom_wac_battery_report(struct hid_device *hdev,
		struct hid_report *report)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;

	if (features->quirks & WACOM_QUIRK_BATTERY) {
		int status = wacom_wac->hid_data.bat_status;
		int capacity = wacom_wac->hid_data.battery_capacity;
		bool charging = wacom_wac->hid_data.bat_charging;
		bool connected = wacom_wac->hid_data.bat_connected;
		bool powered = wacom_wac->hid_data.ps_connected;

		wacom_notify_battery(wacom_wac, status, capacity, charging,
				     connected, powered);
	}
}