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
typedef  int u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct sensor_hub_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int raw_size; int status; scalar_t__ raw_data; int /*<<< orphan*/  ready; void* attr_usage_id; void* usage_id; } ;
struct hid_sensor_hub_device {int /*<<< orphan*/ * mutex_ptr; TYPE_1__ pending; int /*<<< orphan*/  hdev; } ;
struct hid_report {int dummy; } ;
typedef  int s8 ;
typedef  int s16 ;
typedef  enum sensor_hub_read_flags { ____Placeholder_sensor_hub_read_flags } sensor_hub_read_flags ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int HZ ; 
 int SENSOR_HUB_SYNC ; 
 struct sensor_hub_data* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_request (int /*<<< orphan*/ ,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hid_report* sensor_hub_report (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

int sensor_hub_input_attr_get_raw_value(struct hid_sensor_hub_device *hsdev,
					u32 usage_id,
					u32 attr_usage_id, u32 report_id,
					enum sensor_hub_read_flags flag,
					bool is_signed)
{
	struct sensor_hub_data *data = hid_get_drvdata(hsdev->hdev);
	unsigned long flags;
	struct hid_report *report;
	int ret_val = 0;

	report = sensor_hub_report(report_id, hsdev->hdev,
				   HID_INPUT_REPORT);
	if (!report)
		return -EINVAL;

	mutex_lock(hsdev->mutex_ptr);
	if (flag == SENSOR_HUB_SYNC) {
		memset(&hsdev->pending, 0, sizeof(hsdev->pending));
		init_completion(&hsdev->pending.ready);
		hsdev->pending.usage_id = usage_id;
		hsdev->pending.attr_usage_id = attr_usage_id;
		hsdev->pending.raw_size = 0;

		spin_lock_irqsave(&data->lock, flags);
		hsdev->pending.status = true;
		spin_unlock_irqrestore(&data->lock, flags);
	}
	mutex_lock(&data->mutex);
	hid_hw_request(hsdev->hdev, report, HID_REQ_GET_REPORT);
	mutex_unlock(&data->mutex);
	if (flag == SENSOR_HUB_SYNC) {
		wait_for_completion_interruptible_timeout(
						&hsdev->pending.ready, HZ*5);
		switch (hsdev->pending.raw_size) {
		case 1:
			if (is_signed)
				ret_val = *(s8 *)hsdev->pending.raw_data;
			else
				ret_val = *(u8 *)hsdev->pending.raw_data;
			break;
		case 2:
			if (is_signed)
				ret_val = *(s16 *)hsdev->pending.raw_data;
			else
				ret_val = *(u16 *)hsdev->pending.raw_data;
			break;
		case 4:
			ret_val = *(u32 *)hsdev->pending.raw_data;
			break;
		default:
			ret_val = 0;
		}
		kfree(hsdev->pending.raw_data);
		hsdev->pending.status = false;
	}
	mutex_unlock(hsdev->mutex_ptr);

	return ret_val;
}