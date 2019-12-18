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
typedef  int u8 ;
struct TYPE_4__ {int id; int dev_id_byte; int re_lsb; } ;
struct TYPE_3__ {int id; scalar_t__ inrange; scalar_t__ fragmented_hires; } ;
struct uclogic_params {int pen_frame_flag; TYPE_2__ frame; TYPE_1__ pen; int /*<<< orphan*/  pen_unused; } ;
struct uclogic_drvdata {int re_state; int /*<<< orphan*/  inrange_timer; struct uclogic_params params; } ;
struct hid_report {scalar_t__ type; int id; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HID_INPUT_REPORT ; 
 scalar_t__ UCLOGIC_PARAMS_PEN_INRANGE_INVERTED ; 
 scalar_t__ UCLOGIC_PARAMS_PEN_INRANGE_NONE ; 
 struct uclogic_drvdata* hid_get_drvdata (struct hid_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static int uclogic_raw_event(struct hid_device *hdev,
				struct hid_report *report,
				u8 *data, int size)
{
	struct uclogic_drvdata *drvdata = hid_get_drvdata(hdev);
	struct uclogic_params *params = &drvdata->params;

	/* Tweak pen reports, if necessary */
	if (!params->pen_unused &&
	    (report->type == HID_INPUT_REPORT) &&
	    (report->id == params->pen.id) &&
	    (size >= 2)) {
		/* If it's the "virtual" frame controls report */
		if (params->frame.id != 0 &&
		    data[1] & params->pen_frame_flag) {
			/* Change to virtual frame controls report ID */
			data[0] = params->frame.id;
			return 0;
		}
		/* If in-range reports are inverted */
		if (params->pen.inrange ==
			UCLOGIC_PARAMS_PEN_INRANGE_INVERTED) {
			/* Invert the in-range bit */
			data[1] ^= 0x40;
		}
		/*
		 * If report contains fragmented high-resolution pen
		 * coordinates
		 */
		if (size >= 10 && params->pen.fragmented_hires) {
			u8 pressure_low_byte;
			u8 pressure_high_byte;

			/* Lift pressure bytes */
			pressure_low_byte = data[6];
			pressure_high_byte = data[7];
			/*
			 * Move Y coord to make space for high-order X
			 * coord byte
			 */
			data[6] = data[5];
			data[5] = data[4];
			/* Move high-order X coord byte */
			data[4] = data[8];
			/* Move high-order Y coord byte */
			data[7] = data[9];
			/* Place pressure bytes */
			data[8] = pressure_low_byte;
			data[9] = pressure_high_byte;
		}
		/* If we need to emulate in-range detection */
		if (params->pen.inrange == UCLOGIC_PARAMS_PEN_INRANGE_NONE) {
			/* Set in-range bit */
			data[1] |= 0x40;
			/* (Re-)start in-range timeout */
			mod_timer(&drvdata->inrange_timer,
					jiffies + msecs_to_jiffies(100));
		}
	}

	/* Tweak frame control reports, if necessary */
	if ((report->type == HID_INPUT_REPORT) &&
	    (report->id == params->frame.id)) {
		/* If need to, and can, set pad device ID for Wacom drivers */
		if (params->frame.dev_id_byte > 0 &&
		    params->frame.dev_id_byte < size) {
			data[params->frame.dev_id_byte] = 0xf;
		}
		/* If need to, and can, read rotary encoder state change */
		if (params->frame.re_lsb > 0 &&
		    params->frame.re_lsb / 8 < size) {
			unsigned int byte = params->frame.re_lsb / 8;
			unsigned int bit = params->frame.re_lsb % 8;

			u8 change;
			u8 prev_state = drvdata->re_state;
			/* Read Gray-coded state */
			u8 state = (data[byte] >> bit) & 0x3;
			/* Encode state change into 2-bit signed integer */
			if ((prev_state == 1 && state == 0) ||
			    (prev_state == 2 && state == 3)) {
				change = 1;
			} else if ((prev_state == 2 && state == 0) ||
				   (prev_state == 1 && state == 3)) {
				change = 3;
			} else {
				change = 0;
			}
			/* Write change */
			data[byte] = (data[byte] & ~((u8)3 << bit)) |
					(change << bit);
			/* Remember state */
			drvdata->re_state = state;
		}
	}

	return 0;
}