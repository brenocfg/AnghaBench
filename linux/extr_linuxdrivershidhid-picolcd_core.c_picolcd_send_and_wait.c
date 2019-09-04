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
struct picolcd_pending {int /*<<< orphan*/  ready; scalar_t__ raw_size; int /*<<< orphan*/ * in_report; struct hid_report* out_report; } ;
struct picolcd_data {int status; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; struct picolcd_pending* pending; int /*<<< orphan*/  hdev; } ;
struct hid_report {int maxfield; TYPE_1__** field; } ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int report_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int HZ ; 
 int PICOLCD_FAILED ; 
 struct picolcd_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_request (int /*<<< orphan*/ ,struct hid_report*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_set_field (TYPE_1__*,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct picolcd_pending*) ; 
 struct picolcd_pending* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hid_report* picolcd_out_report (int,struct hid_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

struct picolcd_pending *picolcd_send_and_wait(struct hid_device *hdev,
		int report_id, const u8 *raw_data, int size)
{
	struct picolcd_data *data = hid_get_drvdata(hdev);
	struct picolcd_pending *work;
	struct hid_report *report = picolcd_out_report(report_id, hdev);
	unsigned long flags;
	int i, j, k;

	if (!report || !data)
		return NULL;
	if (data->status & PICOLCD_FAILED)
		return NULL;
	work = kzalloc(sizeof(*work), GFP_KERNEL);
	if (!work)
		return NULL;

	init_completion(&work->ready);
	work->out_report = report;
	work->in_report  = NULL;
	work->raw_size   = 0;

	mutex_lock(&data->mutex);
	spin_lock_irqsave(&data->lock, flags);
	for (i = k = 0; i < report->maxfield; i++)
		for (j = 0; j < report->field[i]->report_count; j++) {
			hid_set_field(report->field[i], j, k < size ? raw_data[k] : 0);
			k++;
		}
	if (data->status & PICOLCD_FAILED) {
		kfree(work);
		work = NULL;
	} else {
		data->pending = work;
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
		spin_unlock_irqrestore(&data->lock, flags);
		wait_for_completion_interruptible_timeout(&work->ready, HZ*2);
		spin_lock_irqsave(&data->lock, flags);
		data->pending = NULL;
	}
	spin_unlock_irqrestore(&data->lock, flags);
	mutex_unlock(&data->mutex);
	return work;
}