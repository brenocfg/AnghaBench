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
struct sensor_hub_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ref_cnt; } ;
struct hid_sensor_hub_device {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*) ; 
 struct sensor_hub_data* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 int hid_hw_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int sensor_hub_device_open(struct hid_sensor_hub_device *hsdev)
{
	int ret = 0;
	struct sensor_hub_data *data =  hid_get_drvdata(hsdev->hdev);

	mutex_lock(&data->mutex);
	if (!data->ref_cnt) {
		ret = hid_hw_open(hsdev->hdev);
		if (ret) {
			hid_err(hsdev->hdev, "failed to open hid device\n");
			mutex_unlock(&data->mutex);
			return ret;
		}
	}
	data->ref_cnt++;
	mutex_unlock(&data->mutex);

	return ret;
}