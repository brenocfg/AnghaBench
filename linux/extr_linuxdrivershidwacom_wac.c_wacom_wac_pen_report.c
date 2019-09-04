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
struct TYPE_4__ {int inrange_state; int sense_state; int barrelswitch; int barrelswitch2; int tipswitch; scalar_t__ invert_state; } ;
struct wacom_wac {int* id; int* serial; scalar_t__* tool; TYPE_2__ hid_data; TYPE_1__* shared; scalar_t__ is_invalid_bt_frame; struct input_dev* pen_input; } ;
struct wacom {struct wacom_wac wacom_wac; } ;
struct input_dev {int dummy; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;
struct TYPE_3__ {int stylus_in_proximity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 scalar_t__ BTN_STYLUS ; 
 scalar_t__ BTN_STYLUS2 ; 
 scalar_t__ BTN_STYLUS3 ; 
 scalar_t__ BTN_TOOL_PEN ; 
 scalar_t__ BTN_TOOL_RUBBER ; 
 scalar_t__ BTN_TOUCH ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  delay_pen_events (struct wacom_wac*) ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ wacom_intuos_get_tool_type (int) ; 
 int wacom_intuos_id_mangle (int) ; 

__attribute__((used)) static void wacom_wac_pen_report(struct hid_device *hdev,
		struct hid_report *report)
{
	struct wacom *wacom = hid_get_drvdata(hdev);
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct input_dev *input = wacom_wac->pen_input;
	bool range = wacom_wac->hid_data.inrange_state;
	bool sense = wacom_wac->hid_data.sense_state;

	if (wacom_wac->is_invalid_bt_frame)
		return;

	if (!wacom_wac->tool[0] && range) { /* first in range */
		/* Going into range select tool */
		if (wacom_wac->hid_data.invert_state)
			wacom_wac->tool[0] = BTN_TOOL_RUBBER;
		else if (wacom_wac->id[0])
			wacom_wac->tool[0] = wacom_intuos_get_tool_type(wacom_wac->id[0]);
		else
			wacom_wac->tool[0] = BTN_TOOL_PEN;
	}

	/* keep pen state for touch events */
	wacom_wac->shared->stylus_in_proximity = sense;

	if (!delay_pen_events(wacom_wac) && wacom_wac->tool[0]) {
		int id = wacom_wac->id[0];
		int sw_state = wacom_wac->hid_data.barrelswitch |
			       (wacom_wac->hid_data.barrelswitch2 << 1);

		input_report_key(input, BTN_STYLUS, sw_state == 1);
		input_report_key(input, BTN_STYLUS2, sw_state == 2);
		input_report_key(input, BTN_STYLUS3, sw_state == 3);

		/*
		 * Non-USI EMR tools should have their IDs mangled to
		 * match the legacy behavior of wacom_intuos_general
		 */
		if (wacom_wac->serial[0] >> 52 == 1)
			id = wacom_intuos_id_mangle(id);

		/*
		 * To ensure compatibility with xf86-input-wacom, we should
		 * report the BTN_TOOL_* event prior to the ABS_MISC or
		 * MSC_SERIAL events.
		 */
		input_report_key(input, BTN_TOUCH,
				wacom_wac->hid_data.tipswitch);
		input_report_key(input, wacom_wac->tool[0], sense);
		if (wacom_wac->serial[0]) {
			input_event(input, EV_MSC, MSC_SERIAL, wacom_wac->serial[0]);
			input_report_abs(input, ABS_MISC, sense ? id : 0);
		}

		wacom_wac->hid_data.tipswitch = false;

		input_sync(input);
	}

	if (!sense) {
		wacom_wac->tool[0] = 0;
		wacom_wac->id[0] = 0;
		wacom_wac->serial[0] = 0;
	}
}