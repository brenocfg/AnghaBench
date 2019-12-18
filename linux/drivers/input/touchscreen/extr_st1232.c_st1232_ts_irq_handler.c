#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st1232_ts_finger {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  t; int /*<<< orphan*/  is_valid; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dev; } ;
struct st1232_ts_data {TYPE_3__ low_latency_req; TYPE_2__* client; int /*<<< orphan*/  prop; TYPE_1__* chip_info; struct input_dev* input_dev; struct st1232_ts_finger* finger; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int max_fingers; scalar_t__ have_z; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  DEV_PM_QOS_RESUME_LATENCY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_pm_qos_add_ancestor_request (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_pm_qos_remove_request (TYPE_3__*) ; 
 int /*<<< orphan*/  input_mt_sync (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int st1232_ts_read_data (struct st1232_ts_data*) ; 
 int /*<<< orphan*/  touchscreen_report_pos (struct input_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t st1232_ts_irq_handler(int irq, void *dev_id)
{
	struct st1232_ts_data *ts = dev_id;
	struct st1232_ts_finger *finger = ts->finger;
	struct input_dev *input_dev = ts->input_dev;
	int count = 0;
	int i, ret;

	ret = st1232_ts_read_data(ts);
	if (ret < 0)
		goto end;

	/* multi touch protocol */
	for (i = 0; i < ts->chip_info->max_fingers; i++) {
		if (!finger[i].is_valid)
			continue;

		if (ts->chip_info->have_z)
			input_report_abs(input_dev, ABS_MT_TOUCH_MAJOR,
					 finger[i].t);

		touchscreen_report_pos(input_dev, &ts->prop,
					finger[i].x, finger[i].y, true);
		input_mt_sync(input_dev);
		count++;
	}

	/* SYN_MT_REPORT only if no contact */
	if (!count) {
		input_mt_sync(input_dev);
		if (ts->low_latency_req.dev) {
			dev_pm_qos_remove_request(&ts->low_latency_req);
			ts->low_latency_req.dev = NULL;
		}
	} else if (!ts->low_latency_req.dev) {
		/* First contact, request 100 us latency. */
		dev_pm_qos_add_ancestor_request(&ts->client->dev,
						&ts->low_latency_req,
						DEV_PM_QOS_RESUME_LATENCY, 100);
	}

	/* SYN_REPORT */
	input_sync(input_dev);

end:
	return IRQ_HANDLED;
}