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
 struct sensor_hub_data* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void sensor_hub_device_close(struct hid_sensor_hub_device *hsdev)
{
	struct sensor_hub_data *data =  hid_get_drvdata(hsdev->hdev);

	mutex_lock(&data->mutex);
	data->ref_cnt--;
	if (!data->ref_cnt)
		hid_hw_close(hsdev->hdev);
	mutex_unlock(&data->mutex);
}