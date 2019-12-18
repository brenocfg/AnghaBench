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
struct TYPE_4__ {scalar_t__ type; unsigned char distance_max; } ;
struct wacom_wac {unsigned char* data; int* serial; unsigned char* id; TYPE_1__* shared; scalar_t__* tool; TYPE_2__ features; struct input_dev* pen_input; } ;
struct input_dev {int dummy; } ;
typedef  int int16_t ;
struct TYPE_3__ {int stylus_in_proximity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 scalar_t__ BTN_STYLUS ; 
 scalar_t__ BTN_STYLUS2 ; 
 scalar_t__ BTN_TOOL_PEN ; 
 scalar_t__ BTN_TOOL_RUBBER ; 
 scalar_t__ BTN_TOUCH ; 
 int /*<<< orphan*/  EV_MSC ; 
 scalar_t__ INTUOSP2S_BT ; 
 scalar_t__ INTUOSP2_BT ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 unsigned char get_unaligned_le16 (unsigned char*) ; 
 void* get_unaligned_le64 (unsigned char*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  wacom_exit_report (struct wacom_wac*) ; 
 scalar_t__ wacom_intuos_get_tool_type (int) ; 
 unsigned char wacom_intuos_id_mangle (int) ; 

__attribute__((used)) static void wacom_intuos_pro2_bt_pen(struct wacom_wac *wacom)
{
	int pen_frame_len, pen_frames;

	struct input_dev *pen_input = wacom->pen_input;
	unsigned char *data = wacom->data;
	int i;

	if (wacom->features.type == INTUOSP2_BT ||
	    wacom->features.type == INTUOSP2S_BT) {
		wacom->serial[0] = get_unaligned_le64(&data[99]);
		wacom->id[0]     = get_unaligned_le16(&data[107]);
		pen_frame_len = 14;
		pen_frames = 7;
	} else {
		wacom->serial[0] = get_unaligned_le64(&data[33]);
		wacom->id[0]     = get_unaligned_le16(&data[41]);
		pen_frame_len = 8;
		pen_frames = 4;
	}

	if (wacom->serial[0] >> 52 == 1) {
		/* Add back in missing bits of ID for non-USI pens */
		wacom->id[0] |= (wacom->serial[0] >> 32) & 0xFFFFF;
	}

	for (i = 0; i < pen_frames; i++) {
		unsigned char *frame = &data[i*pen_frame_len + 1];
		bool valid = frame[0] & 0x80;
		bool prox = frame[0] & 0x40;
		bool range = frame[0] & 0x20;
		bool invert = frame[0] & 0x10;

		if (!valid)
			continue;

		if (!prox) {
			wacom->shared->stylus_in_proximity = false;
			wacom_exit_report(wacom);
			input_sync(pen_input);

			wacom->tool[0] = 0;
			wacom->id[0] = 0;
			wacom->serial[0] = 0;
			return;
		}

		if (range) {
			if (!wacom->tool[0]) { /* first in range */
				/* Going into range select tool */
				if (invert)
					wacom->tool[0] = BTN_TOOL_RUBBER;
				else if (wacom->id[0])
					wacom->tool[0] = wacom_intuos_get_tool_type(wacom->id[0]);
				else
					wacom->tool[0] = BTN_TOOL_PEN;
			}

			input_report_abs(pen_input, ABS_X, get_unaligned_le16(&frame[1]));
			input_report_abs(pen_input, ABS_Y, get_unaligned_le16(&frame[3]));

			if (wacom->features.type == INTUOSP2_BT ||
			    wacom->features.type == INTUOSP2S_BT) {
				/* Fix rotation alignment: userspace expects zero at left */
				int16_t rotation =
					(int16_t)get_unaligned_le16(&frame[9]);
				rotation += 1800/4;

				if (rotation > 899)
					rotation -= 1800;

				input_report_abs(pen_input, ABS_TILT_X,
						 (char)frame[7]);
				input_report_abs(pen_input, ABS_TILT_Y,
						 (char)frame[8]);
				input_report_abs(pen_input, ABS_Z, rotation);
				input_report_abs(pen_input, ABS_WHEEL,
						 get_unaligned_le16(&frame[11]));
			}
		}
		if (wacom->tool[0]) {
			input_report_abs(pen_input, ABS_PRESSURE, get_unaligned_le16(&frame[5]));
			if (wacom->features.type == INTUOSP2_BT ||
			    wacom->features.type == INTUOSP2S_BT) {
				input_report_abs(pen_input, ABS_DISTANCE,
						 range ? frame[13] : wacom->features.distance_max);
			} else {
				input_report_abs(pen_input, ABS_DISTANCE,
						 range ? frame[7] : wacom->features.distance_max);
			}

			input_report_key(pen_input, BTN_TOUCH, frame[0] & 0x09);
			input_report_key(pen_input, BTN_STYLUS, frame[0] & 0x02);
			input_report_key(pen_input, BTN_STYLUS2, frame[0] & 0x04);

			input_report_key(pen_input, wacom->tool[0], prox);
			input_event(pen_input, EV_MSC, MSC_SERIAL, wacom->serial[0]);
			input_report_abs(pen_input, ABS_MISC,
					 wacom_intuos_id_mangle(wacom->id[0])); /* report tool id */
		}

		wacom->shared->stylus_in_proximity = prox;

		input_sync(pen_input);
	}
}