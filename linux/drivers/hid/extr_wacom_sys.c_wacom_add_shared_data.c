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
struct TYPE_3__ {int device_type; } ;
struct wacom_wac {TYPE_2__* shared; TYPE_1__ features; } ;
struct TYPE_4__ {struct hid_device* pen; struct hid_device* touch; } ;
struct wacom_hdev_data {TYPE_2__ shared; int /*<<< orphan*/  list; struct hid_device* dev; int /*<<< orphan*/  kref; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WACOM_DEVICETYPE_PEN ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int devm_add_action (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct wacom*),struct wacom*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct wacom_hdev_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wacom_hdev_data* wacom_get_hdev_data (struct hid_device*) ; 
 int /*<<< orphan*/  wacom_remove_shared_data (struct wacom*) ; 
 int /*<<< orphan*/  wacom_udev_list ; 
 int /*<<< orphan*/  wacom_udev_list_lock ; 

__attribute__((used)) static int wacom_add_shared_data(struct hid_device *hdev)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_hdev_data *data;
	int retval = 0;

	mutex_lock(&wacom_udev_list_lock);

	data = wacom_get_hdev_data(hdev);
	if (!data) {
		data = kzalloc(sizeof(struct wacom_hdev_data), GFP_KERNEL);
		if (!data) {
			retval = -ENOMEM;
			goto out;
		}

		kref_init(&data->kref);
		data->dev = hdev;
		list_add_tail(&data->list, &wacom_udev_list);
	}

	wacom_wac->shared = &data->shared;

	retval = devm_add_action(&hdev->dev, wacom_remove_shared_data, wacom);
	if (retval) {
		mutex_unlock(&wacom_udev_list_lock);
		wacom_remove_shared_data(wacom);
		return retval;
	}

	if (wacom_wac->features.device_type & WACOM_DEVICETYPE_TOUCH)
		wacom_wac->shared->touch = hdev;
	else if (wacom_wac->features.device_type & WACOM_DEVICETYPE_PEN)
		wacom_wac->shared->pen = hdev;

out:
	mutex_unlock(&wacom_udev_list_lock);
	return retval;
}