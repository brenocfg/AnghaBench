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
struct mt_report_data {scalar_t__ is_mt_collection; } ;
struct mt_device {int dummy; } ;
struct hid_usage {int dummy; } ;
struct hid_field {int /*<<< orphan*/  report; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 struct mt_device* hid_get_drvdata (struct hid_device*) ; 
 struct mt_report_data* mt_find_report_data (struct mt_device*,int /*<<< orphan*/ ) ; 
 int mt_touch_event (struct hid_device*,struct hid_field*,struct hid_usage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt_event(struct hid_device *hid, struct hid_field *field,
				struct hid_usage *usage, __s32 value)
{
	struct mt_device *td = hid_get_drvdata(hid);
	struct mt_report_data *rdata;

	rdata = mt_find_report_data(td, field->report);
	if (rdata && rdata->is_mt_collection)
		return mt_touch_event(hid, field, usage, value);

	return 0;
}