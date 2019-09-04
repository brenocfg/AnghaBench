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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hid_report_enum {int dummy; } ;
struct hid_report {int dummy; } ;
struct hid_driver {int (* raw_event ) (struct hid_device*,struct hid_report*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct hid_device {int /*<<< orphan*/  driver_input_lock; int /*<<< orphan*/  debug_list; struct hid_driver* driver; struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dump_report (struct hid_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hid_report* hid_get_report (struct hid_report_enum*,int /*<<< orphan*/ *) ; 
 scalar_t__ hid_match_report (struct hid_device*,struct hid_report*) ; 
 int hid_report_raw_event (struct hid_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int stub1 (struct hid_device*,struct hid_report*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int hid_input_report(struct hid_device *hid, int type, u8 *data, u32 size, int interrupt)
{
	struct hid_report_enum *report_enum;
	struct hid_driver *hdrv;
	struct hid_report *report;
	int ret = 0;

	if (!hid)
		return -ENODEV;

	if (down_trylock(&hid->driver_input_lock))
		return -EBUSY;

	if (!hid->driver) {
		ret = -ENODEV;
		goto unlock;
	}
	report_enum = hid->report_enum + type;
	hdrv = hid->driver;

	if (!size) {
		dbg_hid("empty report\n");
		ret = -1;
		goto unlock;
	}

	/* Avoid unnecessary overhead if debugfs is disabled */
	if (!list_empty(&hid->debug_list))
		hid_dump_report(hid, type, data, size);

	report = hid_get_report(report_enum, data);

	if (!report) {
		ret = -1;
		goto unlock;
	}

	if (hdrv && hdrv->raw_event && hid_match_report(hid, report)) {
		ret = hdrv->raw_event(hid, report, data, size);
		if (ret < 0)
			goto unlock;
	}

	ret = hid_report_raw_event(hid, type, data, size, interrupt);

unlock:
	up(&hid->driver_input_lock);
	return ret;
}