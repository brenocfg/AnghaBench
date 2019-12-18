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
union sixaxis_output_report_01 {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sony_sc {int* led_state; int quirks; int /*<<< orphan*/  hdev; scalar_t__* led_delay_on; scalar_t__* led_delay_off; int /*<<< orphan*/  left; scalar_t__ right; scalar_t__ output_report_dmabuf; } ;
struct TYPE_3__ {int right_motor_on; int /*<<< orphan*/  left_motor_force; } ;
struct sixaxis_output_report {int leds_bitmap; int /*<<< orphan*/  report_id; TYPE_2__* led; TYPE_1__ rumble; } ;
struct TYPE_4__ {scalar_t__ duty_on; scalar_t__ duty_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  HID_REQ_SET_REPORT ; 
 int SHANWAN_GAMEPAD ; 
 int /*<<< orphan*/  hid_hw_output_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hid_hw_raw_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sixaxis_output_report*,union sixaxis_output_report_01 const*,int) ; 

__attribute__((used)) static void sixaxis_send_output_report(struct sony_sc *sc)
{
	static const union sixaxis_output_report_01 default_report = {
		.buf = {
			0x01,
			0x01, 0xff, 0x00, 0xff, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0x00, 0x00, 0x00, 0x00, 0x00
		}
	};
	struct sixaxis_output_report *report =
		(struct sixaxis_output_report *)sc->output_report_dmabuf;
	int n;

	/* Initialize the report with default values */
	memcpy(report, &default_report, sizeof(struct sixaxis_output_report));

#ifdef CONFIG_SONY_FF
	report->rumble.right_motor_on = sc->right ? 1 : 0;
	report->rumble.left_motor_force = sc->left;
#endif

	report->leds_bitmap |= sc->led_state[0] << 1;
	report->leds_bitmap |= sc->led_state[1] << 2;
	report->leds_bitmap |= sc->led_state[2] << 3;
	report->leds_bitmap |= sc->led_state[3] << 4;

	/* Set flag for all leds off, required for 3rd party INTEC controller */
	if ((report->leds_bitmap & 0x1E) == 0)
		report->leds_bitmap |= 0x20;

	/*
	 * The LEDs in the report are indexed in reverse order to their
	 * corresponding light on the controller.
	 * Index 0 = LED 4, index 1 = LED 3, etc...
	 *
	 * In the case of both delay values being zero (blinking disabled) the
	 * default report values should be used or the controller LED will be
	 * always off.
	 */
	for (n = 0; n < 4; n++) {
		if (sc->led_delay_on[n] || sc->led_delay_off[n]) {
			report->led[3 - n].duty_off = sc->led_delay_off[n];
			report->led[3 - n].duty_on = sc->led_delay_on[n];
		}
	}

	/* SHANWAN controllers require output reports via intr channel */
	if (sc->quirks & SHANWAN_GAMEPAD)
		hid_hw_output_report(sc->hdev, (u8 *)report,
				sizeof(struct sixaxis_output_report));
	else
		hid_hw_raw_request(sc->hdev, report->report_id, (u8 *)report,
				sizeof(struct sixaxis_output_report),
				HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
}