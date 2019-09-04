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
struct TYPE_2__ {int /*<<< orphan*/  maxcontacts; } ;
struct mt_device {int is_buttonpad; TYPE_1__ mtclass; int /*<<< orphan*/  maxcontacts; } ;
struct hid_usage {int hid; size_t usage_index; } ;
struct hid_field {size_t report_count; int /*<<< orphan*/  report; int /*<<< orphan*/ * value; int /*<<< orphan*/  logical_maximum; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HID_DG_BUTTONTYPE 129 
#define  HID_DG_CONTACTMAX 128 
 int /*<<< orphan*/  MT_BUTTONTYPE_CLICKPAD ; 
 int /*<<< orphan*/  MT_MAX_MAXCONTACT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mt_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  mt_get_feature (struct hid_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt_feature_mapping(struct hid_device *hdev,
		struct hid_field *field, struct hid_usage *usage)
{
	struct mt_device *td = hid_get_drvdata(hdev);

	switch (usage->hid) {
	case HID_DG_CONTACTMAX:
		mt_get_feature(hdev, field->report);

		td->maxcontacts = field->value[0];
		if (!td->maxcontacts &&
		    field->logical_maximum <= MT_MAX_MAXCONTACT)
			td->maxcontacts = field->logical_maximum;
		if (td->mtclass.maxcontacts)
			/* check if the maxcontacts is given by the class */
			td->maxcontacts = td->mtclass.maxcontacts;

		break;
	case HID_DG_BUTTONTYPE:
		if (usage->usage_index >= field->report_count) {
			dev_err(&hdev->dev, "HID_DG_BUTTONTYPE out of range\n");
			break;
		}

		mt_get_feature(hdev, field->report);
		if (field->value[usage->usage_index] == MT_BUTTONTYPE_CLICKPAD)
			td->is_buttonpad = true;

		break;
	case 0xff0000c5:
		/* Retrieve the Win8 blob once to enable some devices */
		if (usage->usage_index == 0)
			mt_get_feature(hdev, field->report);
		break;
	}
}