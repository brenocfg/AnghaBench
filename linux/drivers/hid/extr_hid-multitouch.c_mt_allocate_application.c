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
struct TYPE_4__ {int /*<<< orphan*/  quirks; } ;
struct mt_device {int /*<<< orphan*/  applications; TYPE_2__ mtclass; int /*<<< orphan*/  inputmode_value; TYPE_1__* hdev; } ;
struct mt_application {unsigned int application; int /*<<< orphan*/  list; int /*<<< orphan*/  report_id; int /*<<< orphan*/  quirks; void* raw_cc; void* scantime; int /*<<< orphan*/  mt_flags; int /*<<< orphan*/  mt_usages; } ;
struct hid_report {unsigned int application; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DEFAULT_ZERO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HID_DG_TOUCHPAD ; 
 unsigned int HID_DG_TOUCHSCREEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_MT_DIRECT ; 
 int /*<<< orphan*/  INPUT_MT_POINTER ; 
 int /*<<< orphan*/  MT_INPUTMODE_TOUCHPAD ; 
 struct mt_application* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mt_application *mt_allocate_application(struct mt_device *td,
						      struct hid_report *report)
{
	unsigned int application = report->application;
	struct mt_application *mt_application;

	mt_application = devm_kzalloc(&td->hdev->dev, sizeof(*mt_application),
				      GFP_KERNEL);
	if (!mt_application)
		return NULL;

	mt_application->application = application;
	INIT_LIST_HEAD(&mt_application->mt_usages);

	if (application == HID_DG_TOUCHSCREEN)
		mt_application->mt_flags |= INPUT_MT_DIRECT;

	/*
	 * Model touchscreens providing buttons as touchpads.
	 */
	if (application == HID_DG_TOUCHPAD) {
		mt_application->mt_flags |= INPUT_MT_POINTER;
		td->inputmode_value = MT_INPUTMODE_TOUCHPAD;
	}

	mt_application->scantime = DEFAULT_ZERO;
	mt_application->raw_cc = DEFAULT_ZERO;
	mt_application->quirks = td->mtclass.quirks;
	mt_application->report_id = report->id;

	list_add_tail(&mt_application->list, &td->applications);

	return mt_application;
}