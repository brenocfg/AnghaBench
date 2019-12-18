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
struct sensor_hub_data {int hid_sensor_client_cnt; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; TYPE_1__* hid_sensor_hub_client_devs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ready; scalar_t__ status; } ;
struct hid_sensor_hub_device {TYPE_2__ pending; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct hid_sensor_hub_device* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*) ; 
 struct sensor_hub_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sensor_hub_remove(struct hid_device *hdev)
{
	struct sensor_hub_data *data = hid_get_drvdata(hdev);
	unsigned long flags;
	int i;

	hid_dbg(hdev, " hardware removed\n");
	hid_hw_close(hdev);
	hid_hw_stop(hdev);
	spin_lock_irqsave(&data->lock, flags);
	for (i = 0; i < data->hid_sensor_client_cnt; ++i) {
		struct hid_sensor_hub_device *hsdev =
			data->hid_sensor_hub_client_devs[i].platform_data;
		if (hsdev->pending.status)
			complete(&hsdev->pending.ready);
	}
	spin_unlock_irqrestore(&data->lock, flags);
	mfd_remove_devices(&hdev->dev);
	mutex_destroy(&data->mutex);
}