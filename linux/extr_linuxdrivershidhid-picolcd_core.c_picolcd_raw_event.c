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
typedef  int /*<<< orphan*/  u8 ;
struct picolcd_data {int /*<<< orphan*/  lock; TYPE_1__* pending; scalar_t__ input_keys; } ;
struct hid_report {scalar_t__ id; } ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int raw_size; int /*<<< orphan*/  ready; struct hid_report* in_report; int /*<<< orphan*/  raw_data; } ;

/* Variables and functions */
 scalar_t__ REPORT_IR_DATA ; 
 scalar_t__ REPORT_KEY_STATE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct picolcd_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  picolcd_debug_raw_event (struct picolcd_data*,struct hid_device*,struct hid_report*,int /*<<< orphan*/ *,int) ; 
 int picolcd_raw_cir (struct picolcd_data*,struct hid_report*,int /*<<< orphan*/ *,int) ; 
 int picolcd_raw_keypad (struct picolcd_data*,struct hid_report*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int picolcd_raw_event(struct hid_device *hdev,
		struct hid_report *report, u8 *raw_data, int size)
{
	struct picolcd_data *data = hid_get_drvdata(hdev);
	unsigned long flags;
	int ret = 0;

	if (!data)
		return 1;

	if (size > 64) {
		hid_warn(hdev, "invalid size value (%d) for picolcd raw event (%d)\n",
				size, report->id);
		return 0;
	}

	if (report->id == REPORT_KEY_STATE) {
		if (data->input_keys)
			ret = picolcd_raw_keypad(data, report, raw_data+1, size-1);
	} else if (report->id == REPORT_IR_DATA) {
		ret = picolcd_raw_cir(data, report, raw_data+1, size-1);
	} else {
		spin_lock_irqsave(&data->lock, flags);
		/*
		 * We let the caller of picolcd_send_and_wait() check if the
		 * report we got is one of the expected ones or not.
		 */
		if (data->pending) {
			memcpy(data->pending->raw_data, raw_data+1, size-1);
			data->pending->raw_size  = size-1;
			data->pending->in_report = report;
			complete(&data->pending->ready);
		}
		spin_unlock_irqrestore(&data->lock, flags);
	}

	picolcd_debug_raw_event(data, hdev, report, raw_data, size);
	return 1;
}