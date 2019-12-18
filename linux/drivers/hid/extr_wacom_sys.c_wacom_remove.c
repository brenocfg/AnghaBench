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
struct wacom_features {int device_type; scalar_t__ type; } ;
struct wacom_wac {int /*<<< orphan*/  pen_fifo; struct wacom_features features; } ;
struct wacom {struct wacom_wac wacom_wac; int /*<<< orphan*/  mode_change_work; int /*<<< orphan*/  remote_work; int /*<<< orphan*/  battery_work; int /*<<< orphan*/  wireless_work; int /*<<< orphan*/  init_work; } ;
struct hid_device {scalar_t__ bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BUS_BLUETOOTH ; 
 scalar_t__ REMOTE ; 
 int WACOM_DEVICETYPE_WL_MONITOR ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_speed ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wacom_led_groups_release (struct wacom*) ; 
 int /*<<< orphan*/  wacom_release_resources (struct wacom*) ; 

__attribute__((used)) static void wacom_remove(struct hid_device *hdev)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom_wac->features;

	if (features->device_type & WACOM_DEVICETYPE_WL_MONITOR)
		hid_hw_close(hdev);

	hid_hw_stop(hdev);

	cancel_delayed_work_sync(&wacom->init_work);
	cancel_work_sync(&wacom->wireless_work);
	cancel_work_sync(&wacom->battery_work);
	cancel_work_sync(&wacom->remote_work);
	cancel_work_sync(&wacom->mode_change_work);
	if (hdev->bus == BUS_BLUETOOTH)
		device_remove_file(&hdev->dev, &dev_attr_speed);

	/* make sure we don't trigger the LEDs */
	wacom_led_groups_release(wacom);

	if (wacom->wacom_wac.features.type != REMOTE)
		wacom_release_resources(wacom);

	kfifo_free(&wacom_wac->pen_fifo);
}