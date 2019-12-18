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
typedef  int u8 ;
struct hidpp_device {int /*<<< orphan*/  input; int /*<<< orphan*/  vertical_wheel_counter; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int EINVAL ; 
 int M560_MOUSE_BTN_LEFT ; 
 int M560_MOUSE_BTN_RIGHT ; 
 int M560_MOUSE_BTN_WHEEL_LEFT ; 
 int M560_MOUSE_BTN_WHEEL_RIGHT ; 
 int M560_SUB_ID ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_HWHEEL_HI_RES ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int REPORT_ID_HIDPP_LONG ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_field_extract (struct hid_device*,int*,int,int) ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int hid_snto32 (int,int) ; 
 int /*<<< orphan*/  hidpp_scroll_counter_handle_scroll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m560_raw_event(struct hid_device *hdev, u8 *data, int size)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);

	/* sanity check */
	if (!hidpp->input) {
		hid_err(hdev, "error in parameter\n");
		return -EINVAL;
	}

	if (size < 7) {
		hid_err(hdev, "error in report\n");
		return 0;
	}

	if (data[0] == REPORT_ID_HIDPP_LONG &&
	    data[2] == M560_SUB_ID && data[6] == 0x00) {
		/*
		 * m560 mouse report for middle, forward and backward button
		 *
		 * data[0] = 0x11
		 * data[1] = device-id
		 * data[2] = 0x0a
		 * data[5] = 0xaf -> middle
		 *	     0xb0 -> forward
		 *	     0xae -> backward
		 *	     0x00 -> release all
		 * data[6] = 0x00
		 */

		switch (data[5]) {
		case 0xaf:
			input_report_key(hidpp->input, BTN_MIDDLE, 1);
			break;
		case 0xb0:
			input_report_key(hidpp->input, BTN_FORWARD, 1);
			break;
		case 0xae:
			input_report_key(hidpp->input, BTN_BACK, 1);
			break;
		case 0x00:
			input_report_key(hidpp->input, BTN_BACK, 0);
			input_report_key(hidpp->input, BTN_FORWARD, 0);
			input_report_key(hidpp->input, BTN_MIDDLE, 0);
			break;
		default:
			hid_err(hdev, "error in report\n");
			return 0;
		}
		input_sync(hidpp->input);

	} else if (data[0] == 0x02) {
		/*
		 * Logitech M560 mouse report
		 *
		 * data[0] = type (0x02)
		 * data[1..2] = buttons
		 * data[3..5] = xy
		 * data[6] = wheel
		 */

		int v;

		input_report_key(hidpp->input, BTN_LEFT,
			!!(data[1] & M560_MOUSE_BTN_LEFT));
		input_report_key(hidpp->input, BTN_RIGHT,
			!!(data[1] & M560_MOUSE_BTN_RIGHT));

		if (data[1] & M560_MOUSE_BTN_WHEEL_LEFT) {
			input_report_rel(hidpp->input, REL_HWHEEL, -1);
			input_report_rel(hidpp->input, REL_HWHEEL_HI_RES,
					 -120);
		} else if (data[1] & M560_MOUSE_BTN_WHEEL_RIGHT) {
			input_report_rel(hidpp->input, REL_HWHEEL, 1);
			input_report_rel(hidpp->input, REL_HWHEEL_HI_RES,
					 120);
		}

		v = hid_snto32(hid_field_extract(hdev, data+3, 0, 12), 12);
		input_report_rel(hidpp->input, REL_X, v);

		v = hid_snto32(hid_field_extract(hdev, data+3, 12, 12), 12);
		input_report_rel(hidpp->input, REL_Y, v);

		v = hid_snto32(data[6], 8);
		if (v != 0)
			hidpp_scroll_counter_handle_scroll(hidpp->input,
					&hidpp->vertical_wheel_counter, v);

		input_sync(hidpp->input);
	}

	return 1;
}