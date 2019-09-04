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
struct mt_report_data {scalar_t__ is_mt_collection; } ;
struct mt_device {int dummy; } ;
struct hid_report {struct hid_field** field; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
struct TYPE_2__ {scalar_t__ input; } ;

/* Variables and functions */
 int HID_CLAIMED_INPUT ; 
 struct mt_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 
 struct mt_report_data* mt_find_report_data (struct mt_device*,struct hid_report*) ; 
 void mt_touch_report (struct hid_device*,struct mt_report_data*) ; 

__attribute__((used)) static void mt_report(struct hid_device *hid, struct hid_report *report)
{
	struct mt_device *td = hid_get_drvdata(hid);
	struct hid_field *field = report->field[0];
	struct mt_report_data *rdata;

	if (!(hid->claimed & HID_CLAIMED_INPUT))
		return;

	rdata = mt_find_report_data(td, report);
	if (rdata && rdata->is_mt_collection)
		return mt_touch_report(hid, rdata);

	if (field && field->hidinput && field->hidinput->input)
		input_sync(field->hidinput->input);
}