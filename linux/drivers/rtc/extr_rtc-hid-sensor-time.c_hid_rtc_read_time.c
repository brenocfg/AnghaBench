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
struct rtc_time {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hsdev; } ;
struct hid_time_state {int /*<<< orphan*/  lock_last_time; struct rtc_time last_time; int /*<<< orphan*/  comp_last_time; TYPE_2__* info; TYPE_1__ common_attributes; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  report_id; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_TIME ; 
 int HZ ; 
 int /*<<< orphan*/  SENSOR_HUB_SYNC ; 
 struct hid_time_state* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * hid_time_addresses ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sensor_hub_input_attr_get_raw_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hid_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long flags;
	struct hid_time_state *time_state = dev_get_drvdata(dev);
	int ret;

	reinit_completion(&time_state->comp_last_time);
	/* get a report with all values through requesting one value */
	sensor_hub_input_attr_get_raw_value(time_state->common_attributes.hsdev,
			HID_USAGE_SENSOR_TIME, hid_time_addresses[0],
			time_state->info[0].report_id, SENSOR_HUB_SYNC, false);
	/* wait for all values (event) */
	ret = wait_for_completion_killable_timeout(
			&time_state->comp_last_time, HZ*6);
	if (ret > 0) {
		/* no error */
		spin_lock_irqsave(&time_state->lock_last_time, flags);
		*tm = time_state->last_time;
		spin_unlock_irqrestore(&time_state->lock_last_time, flags);
		return 0;
	}
	if (!ret)
		return -EIO; /* timeouted */
	return ret; /* killed (-ERESTARTSYS) */
}