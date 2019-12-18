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
struct wacom_features {int numbered_buttons; scalar_t__ type; scalar_t__ oPid; } ;
struct wacom_wac {unsigned char* data; scalar_t__* tool; TYPE_1__* shared; struct input_dev* pad_input; struct wacom_features features; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int is_touch_on; scalar_t__ touch_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 scalar_t__ CINTIQ_COMPANION_2 ; 
 scalar_t__ CINTIQ_HYBRID ; 
 scalar_t__ DTK ; 
 int /*<<< orphan*/  EV_MSC ; 
 scalar_t__ INTUOS4L ; 
 scalar_t__ INTUOS4S ; 
 scalar_t__ INTUOS5S ; 
 scalar_t__ INTUOSPL ; 
 scalar_t__ KEY_BUTTONCONFIG ; 
 scalar_t__ KEY_CONTROLPANEL ; 
 scalar_t__ KEY_INFO ; 
 scalar_t__ KEY_ONSCREEN_KEYBOARD ; 
 scalar_t__ KEY_PROG1 ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int PAD_DEVICE_ID ; 
 int /*<<< orphan*/  SW_MUTE_DEVICE ; 
 scalar_t__ WACOM_13HD ; 
 scalar_t__ WACOM_21UX2 ; 
 scalar_t__ WACOM_22HD ; 
 scalar_t__ WACOM_24HD ; 
 scalar_t__ WACOM_27QHD ; 
 unsigned char WACOM_REPORT_CINTIQPAD ; 
 unsigned char WACOM_REPORT_INTUOS5PAD ; 
 unsigned char WACOM_REPORT_INTUOSPAD ; 
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_report_switch (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 
 int /*<<< orphan*/  wacom_report_numbered_buttons (struct input_dev*,int,int) ; 

__attribute__((used)) static int wacom_intuos_pad(struct wacom_wac *wacom)
{
	struct wacom_features *features = &wacom->features;
	unsigned char *data = wacom->data;
	struct input_dev *input = wacom->pad_input;
	int i;
	int buttons = 0, nbuttons = features->numbered_buttons;
	int keys = 0, nkeys = 0;
	int ring1 = 0, ring2 = 0;
	int strip1 = 0, strip2 = 0;
	bool prox = false;
	bool wrench = false, keyboard = false, mute_touch = false, menu = false,
	     info = false;

	/* pad packets. Works as a second tool and is always in prox */
	if (!(data[0] == WACOM_REPORT_INTUOSPAD || data[0] == WACOM_REPORT_INTUOS5PAD ||
	      data[0] == WACOM_REPORT_CINTIQPAD))
		return 0;

	if (features->type >= INTUOS4S && features->type <= INTUOS4L) {
		buttons = (data[3] << 1) | (data[2] & 0x01);
		ring1 = data[1];
	} else if (features->type == DTK) {
		buttons = data[6];
	} else if (features->type == WACOM_13HD) {
		buttons = (data[4] << 1) | (data[3] & 0x01);
	} else if (features->type == WACOM_24HD) {
		buttons = (data[8] << 8) | data[6];
		ring1 = data[1];
		ring2 = data[2];

		/*
		 * Three "buttons" are available on the 24HD which are
		 * physically implemented as a touchstrip. Each button
		 * is approximately 3 bits wide with a 2 bit spacing.
		 * The raw touchstrip bits are stored at:
		 *    ((data[3] & 0x1f) << 8) | data[4])
		 */
		nkeys = 3;
		keys = ((data[3] & 0x1C) ? 1<<2 : 0) |
		       ((data[4] & 0xE0) ? 1<<1 : 0) |
		       ((data[4] & 0x07) ? 1<<0 : 0);
		keyboard = !!(data[4] & 0xE0);
		info = !!(data[3] & 0x1C);

		if (features->oPid) {
			mute_touch = !!(data[4] & 0x07);
			if (mute_touch)
				wacom->shared->is_touch_on =
					!wacom->shared->is_touch_on;
		} else {
			wrench = !!(data[4] & 0x07);
		}
	} else if (features->type == WACOM_27QHD) {
		nkeys = 3;
		keys = data[2] & 0x07;

		wrench = !!(data[2] & 0x01);
		keyboard = !!(data[2] & 0x02);

		if (features->oPid) {
			mute_touch = !!(data[2] & 0x04);
			if (mute_touch)
				wacom->shared->is_touch_on =
					!wacom->shared->is_touch_on;
		} else {
			menu = !!(data[2] & 0x04);
		}
		input_report_abs(input, ABS_X, be16_to_cpup((__be16 *)&data[4]));
		input_report_abs(input, ABS_Y, be16_to_cpup((__be16 *)&data[6]));
		input_report_abs(input, ABS_Z, be16_to_cpup((__be16 *)&data[8]));
	} else if (features->type == CINTIQ_HYBRID) {
		/*
		 * Do not send hardware buttons under Android. They
		 * are already sent to the system through GPIO (and
		 * have different meaning).
		 *
		 * d-pad right  -> data[4] & 0x10
		 * d-pad up     -> data[4] & 0x20
		 * d-pad left   -> data[4] & 0x40
		 * d-pad down   -> data[4] & 0x80
		 * d-pad center -> data[3] & 0x01
		 */
		buttons = (data[4] << 1) | (data[3] & 0x01);
	} else if (features->type == CINTIQ_COMPANION_2) {
		/* d-pad right  -> data[2] & 0x10
		 * d-pad up     -> data[2] & 0x20
		 * d-pad left   -> data[2] & 0x40
		 * d-pad down   -> data[2] & 0x80
		 * d-pad center -> data[1] & 0x01
		 */
		buttons = ((data[2] >> 4) << 7) |
		          ((data[1] & 0x04) << 4) |
		          ((data[2] & 0x0F) << 2) |
		          (data[1] & 0x03);
	} else if (features->type >= INTUOS5S && features->type <= INTUOSPL) {
		/*
		 * ExpressKeys on Intuos5/Intuos Pro have a capacitive sensor in
		 * addition to the mechanical switch. Switch data is
		 * stored in data[4], capacitive data in data[5].
		 *
		 * Touch ring mode switch (data[3]) has no capacitive sensor
		 */
		buttons = (data[4] << 1) | (data[3] & 0x01);
		ring1 = data[2];
	} else {
		if (features->type == WACOM_21UX2 || features->type == WACOM_22HD) {
			buttons = (data[8] << 10) | ((data[7] & 0x01) << 9) |
			          (data[6] << 1) | (data[5] & 0x01);

			if (features->type == WACOM_22HD) {
				nkeys = 3;
				keys = data[9] & 0x07;

				info = !!(data[9] & 0x01);
				wrench = !!(data[9] & 0x02);
			}
		} else {
			buttons = ((data[6] & 0x10) << 5)  |
			          ((data[5] & 0x10) << 4)  |
			          ((data[6] & 0x0F) << 4)  |
			          (data[5] & 0x0F);
		}
		strip1 = ((data[1] & 0x1f) << 8) | data[2];
		strip2 = ((data[3] & 0x1f) << 8) | data[4];
	}

	prox = (buttons & ~(~0U << nbuttons)) | (keys & ~(~0U << nkeys)) |
	       (ring1 & 0x80) | (ring2 & 0x80) | strip1 | strip2;

	wacom_report_numbered_buttons(input, nbuttons, buttons);

	for (i = 0; i < nkeys; i++)
		input_report_key(input, KEY_PROG1 + i, keys & (1 << i));

	input_report_key(input, KEY_BUTTONCONFIG, wrench);
	input_report_key(input, KEY_ONSCREEN_KEYBOARD, keyboard);
	input_report_key(input, KEY_CONTROLPANEL, menu);
	input_report_key(input, KEY_INFO, info);

	if (wacom->shared && wacom->shared->touch_input) {
		input_report_switch(wacom->shared->touch_input,
				    SW_MUTE_DEVICE,
				    !wacom->shared->is_touch_on);
		input_sync(wacom->shared->touch_input);
	}

	input_report_abs(input, ABS_RX, strip1);
	input_report_abs(input, ABS_RY, strip2);

	input_report_abs(input, ABS_WHEEL,    (ring1 & 0x80) ? (ring1 & 0x7f) : 0);
	input_report_abs(input, ABS_THROTTLE, (ring2 & 0x80) ? (ring2 & 0x7f) : 0);

	input_report_key(input, wacom->tool[1], prox ? 1 : 0);
	input_report_abs(input, ABS_MISC, prox ? PAD_DEVICE_ID : 0);

	input_event(input, EV_MSC, MSC_SERIAL, 0xffffffff);

	return 1;
}