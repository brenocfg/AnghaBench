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
struct mt_application {int quirks; int left_button_state; } ;
struct input_dev {int dummy; } ;
struct hid_usage {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct hid_field {TYPE_1__* hidinput; } ;
struct hid_device {int claimed; } ;
typedef  int __s32 ;
struct TYPE_2__ {struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int HID_CLAIMED_INPUT ; 
 int MT_QUIRK_WIN8_PTP_BUTTONS ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt_process_mt_event(struct hid_device *hid,
				struct mt_application *app,
				struct hid_field *field,
				struct hid_usage *usage,
				__s32 value,
				bool first_packet)
{
	__s32 quirks = app->quirks;
	struct input_dev *input = field->hidinput->input;

	if (!usage->type || !(hid->claimed & HID_CLAIMED_INPUT))
		return;

	if (quirks & MT_QUIRK_WIN8_PTP_BUTTONS) {

		/*
		 * For Win8 PTP touchpads we should only look at
		 * non finger/touch events in the first_packet of a
		 * (possible) multi-packet frame.
		 */
		if (!first_packet)
			return;

		/*
		 * For Win8 PTP touchpads we map both the clickpad click
		 * and any "external" left buttons to BTN_LEFT if a
		 * device claims to have both we need to report 1 for
		 * BTN_LEFT if either is pressed, so we or all values
		 * together and report the result in mt_sync_frame().
		 */
		if (usage->type == EV_KEY && usage->code == BTN_LEFT) {
			app->left_button_state |= value;
			return;
		}
	}

	input_event(input, usage->type, usage->code, value);
}