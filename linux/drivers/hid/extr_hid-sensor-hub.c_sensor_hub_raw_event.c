#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sensor_hub_data {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ attr_usage_id; int raw_size; int /*<<< orphan*/  ready; scalar_t__ raw_data; scalar_t__ status; } ;
struct hid_sensor_hub_device {TYPE_1__ pending; } ;
struct hid_sensor_hub_callbacks {int /*<<< orphan*/  pdev; int /*<<< orphan*/  (* send_event ) (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* capture_sample ) (struct hid_sensor_hub_device*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct hid_report {scalar_t__ type; int maxfield; TYPE_3__** field; int /*<<< orphan*/  id; } ;
struct hid_device {struct hid_collection* collection; } ;
struct hid_collection {int /*<<< orphan*/  usage; } ;
struct TYPE_6__ {int report_size; int report_count; scalar_t__ logical; TYPE_2__* usage; int /*<<< orphan*/  physical; } ;
struct TYPE_5__ {size_t collection_index; scalar_t__ hid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HID_INPUT_REPORT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,...) ; 
 struct sensor_hub_data* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct hid_sensor_hub_callbacks* sensor_hub_get_callback (struct hid_device*,int /*<<< orphan*/ ,size_t,struct hid_sensor_hub_device**,void**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct hid_sensor_hub_device*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hid_sensor_hub_device*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sensor_hub_raw_event(struct hid_device *hdev,
		struct hid_report *report, u8 *raw_data, int size)
{
	int i;
	u8 *ptr;
	int sz;
	struct sensor_hub_data *pdata = hid_get_drvdata(hdev);
	unsigned long flags;
	struct hid_sensor_hub_callbacks *callback = NULL;
	struct hid_collection *collection = NULL;
	void *priv = NULL;
	struct hid_sensor_hub_device *hsdev = NULL;

	hid_dbg(hdev, "sensor_hub_raw_event report id:0x%x size:%d type:%d\n",
			 report->id, size, report->type);
	hid_dbg(hdev, "maxfield:%d\n", report->maxfield);
	if (report->type != HID_INPUT_REPORT)
		return 1;

	ptr = raw_data;
	ptr++; /* Skip report id */

	spin_lock_irqsave(&pdata->lock, flags);

	for (i = 0; i < report->maxfield; ++i) {
		hid_dbg(hdev, "%d collection_index:%x hid:%x sz:%x\n",
				i, report->field[i]->usage->collection_index,
				report->field[i]->usage->hid,
				(report->field[i]->report_size *
					report->field[i]->report_count)/8);
		sz = (report->field[i]->report_size *
					report->field[i]->report_count)/8;
		collection = &hdev->collection[
				report->field[i]->usage->collection_index];
		hid_dbg(hdev, "collection->usage %x\n",
					collection->usage);

		callback = sensor_hub_get_callback(hdev,
				report->field[i]->physical,
				report->field[i]->usage[0].collection_index,
				&hsdev, &priv);
		if (!callback) {
			ptr += sz;
			continue;
		}
		if (hsdev->pending.status && (hsdev->pending.attr_usage_id ==
					      report->field[i]->usage->hid ||
					      hsdev->pending.attr_usage_id ==
					      report->field[i]->logical)) {
			hid_dbg(hdev, "data was pending ...\n");
			hsdev->pending.raw_data = kmemdup(ptr, sz, GFP_ATOMIC);
			if (hsdev->pending.raw_data)
				hsdev->pending.raw_size = sz;
			else
				hsdev->pending.raw_size = 0;
			complete(&hsdev->pending.ready);
		}
		if (callback->capture_sample) {
			if (report->field[i]->logical)
				callback->capture_sample(hsdev,
					report->field[i]->logical, sz, ptr,
					callback->pdev);
			else
				callback->capture_sample(hsdev,
					report->field[i]->usage->hid, sz, ptr,
					callback->pdev);
		}
		ptr += sz;
	}
	if (callback && collection && callback->send_event)
		callback->send_event(hsdev, collection->usage,
				callback->pdev);
	spin_unlock_irqrestore(&pdata->lock, flags);

	return 1;
}