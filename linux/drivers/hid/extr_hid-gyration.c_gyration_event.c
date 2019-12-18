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
struct input_dev {int dummy; } ;
struct hid_usage {int hid; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int HID_CLAIMED_INPUT ; 
 int HID_UP_GENDESK ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static int gyration_event(struct hid_device *hdev, struct hid_field *field,
		struct hid_usage *usage, __s32 value)
{

	if (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput)
		return 0;

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK &&
			(usage->hid & 0xff) == 0x82) {
		struct input_dev *input = field->hidinput->input;
		input_event(input, usage->type, usage->code, 1);
		input_sync(input);
		input_event(input, usage->type, usage->code, 0);
		input_sync(input);
		return 1;
	}

	return 0;
}