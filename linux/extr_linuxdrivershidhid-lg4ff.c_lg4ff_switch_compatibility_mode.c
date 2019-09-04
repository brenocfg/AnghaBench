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
typedef  scalar_t__ u8 ;
struct lg_drv_data {struct lg4ff_device_entry* device_props; } ;
struct lg4ff_device_entry {int /*<<< orphan*/  report_lock; TYPE_2__* report; } ;
struct lg4ff_compat_mode_switch {scalar_t__ cmd_count; int /*<<< orphan*/ * cmd; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {TYPE_1__** field; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_request (struct hid_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_wait (struct hid_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lg4ff_switch_compatibility_mode(struct hid_device *hid, const struct lg4ff_compat_mode_switch *s)
{
	struct lg4ff_device_entry *entry;
	struct lg_drv_data *drv_data;
	unsigned long flags;
	s32 *value;
	u8 i;

	drv_data = hid_get_drvdata(hid);
	if (!drv_data) {
		hid_err(hid, "Private driver data not found!\n");
		return -EINVAL;
	}

	entry = drv_data->device_props;
	if (!entry) {
		hid_err(hid, "Device properties not found!\n");
		return -EINVAL;
	}
	value = entry->report->field[0]->value;

	spin_lock_irqsave(&entry->report_lock, flags);
	for (i = 0; i < s->cmd_count; i++) {
		u8 j;

		for (j = 0; j < 7; j++)
			value[j] = s->cmd[j + (7*i)];

		hid_hw_request(hid, entry->report, HID_REQ_SET_REPORT);
	}
	spin_unlock_irqrestore(&entry->report_lock, flags);
	hid_hw_wait(hid);
	return 0;
}