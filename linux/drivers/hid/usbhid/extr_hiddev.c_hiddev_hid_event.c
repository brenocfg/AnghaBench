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
struct hiddev_usage_ref {int /*<<< orphan*/  value; int /*<<< orphan*/  usage_code; struct hid_usage* usage_index; int /*<<< orphan*/  field_index; int /*<<< orphan*/  report_id; int /*<<< orphan*/  report_type; } ;
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_field {unsigned int report_type; int usage; int /*<<< orphan*/  index; TYPE_1__* report; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 unsigned int HID_FEATURE_REPORT ; 
 unsigned int HID_INPUT_REPORT ; 
 unsigned int HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REPORT_TYPE_FEATURE ; 
 int /*<<< orphan*/  HID_REPORT_TYPE_INPUT ; 
 int /*<<< orphan*/  HID_REPORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  hiddev_send_event (struct hid_device*,struct hiddev_usage_ref*) ; 

void hiddev_hid_event(struct hid_device *hid, struct hid_field *field,
		      struct hid_usage *usage, __s32 value)
{
	unsigned type = field->report_type;
	struct hiddev_usage_ref uref;

	uref.report_type =
	  (type == HID_INPUT_REPORT) ? HID_REPORT_TYPE_INPUT :
	  ((type == HID_OUTPUT_REPORT) ? HID_REPORT_TYPE_OUTPUT :
	   ((type == HID_FEATURE_REPORT) ? HID_REPORT_TYPE_FEATURE : 0));
	uref.report_id = field->report->id;
	uref.field_index = field->index;
	uref.usage_index = (usage - field->usage);
	uref.usage_code = usage->hid;
	uref.value = value;

	hiddev_send_event(hid, &uref);
}