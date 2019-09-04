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
struct TYPE_4__ {int /*<<< orphan*/  input; } ;
struct TYPE_3__ {int flags; int* calib_pro_sticks; } ;
struct wiimote_data {TYPE_2__ extension; TYPE_1__ state; } ;
typedef  int __u8 ;
typedef  int __s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 size_t WIIMOD_PRO_KEY_A ; 
 size_t WIIMOD_PRO_KEY_B ; 
 size_t WIIMOD_PRO_KEY_DOWN ; 
 size_t WIIMOD_PRO_KEY_HOME ; 
 size_t WIIMOD_PRO_KEY_LEFT ; 
 size_t WIIMOD_PRO_KEY_MINUS ; 
 size_t WIIMOD_PRO_KEY_PLUS ; 
 size_t WIIMOD_PRO_KEY_RIGHT ; 
 size_t WIIMOD_PRO_KEY_THUMBL ; 
 size_t WIIMOD_PRO_KEY_THUMBR ; 
 size_t WIIMOD_PRO_KEY_TL ; 
 size_t WIIMOD_PRO_KEY_TR ; 
 size_t WIIMOD_PRO_KEY_UP ; 
 size_t WIIMOD_PRO_KEY_X ; 
 size_t WIIMOD_PRO_KEY_Y ; 
 size_t WIIMOD_PRO_KEY_ZL ; 
 size_t WIIMOD_PRO_KEY_ZR ; 
 int WIIPROTO_FLAG_PRO_CALIB_DONE ; 
 int abs (int) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wiimod_pro_map ; 

__attribute__((used)) static void wiimod_pro_in_ext(struct wiimote_data *wdata, const __u8 *ext)
{
	__s16 rx, ry, lx, ly;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |                   LX <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    2   |  0     0     0     0  |       LX <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    3   |                   RX <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    4   |  0     0     0     0  |       RX <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    5   |                   LY <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    6   |  0     0     0     0  |       LY <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    7   |                   RY <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    8   |  0     0     0     0  |       RY <11:8>       |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    9   | BDR | BDD | BLT | B-  | BH  | B+  | BRT |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   10   | BZL | BB  | BY  | BA  | BX  | BZR | BDL | BDU |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   11   |  1  |     BATTERY     | USB |CHARG|LTHUM|RTHUM|
	 *   -----+-----+-----------------+-----------+-----+-----+
	 * All buttons are low-active (0 if pressed)
	 * RX and RY are right analog stick
	 * LX and LY are left analog stick
	 * BLT is left trigger, BRT is right trigger.
	 * BDR, BDD, BDL, BDU form the D-Pad with right, down, left, up buttons
	 * BZL is left Z button and BZR is right Z button
	 * B-, BH, B+ are +, HOME and - buttons
	 * BB, BY, BA, BX are A, B, X, Y buttons
	 *
	 * Bits marked as 0/1 are unknown and never changed during tests.
	 *
	 * Not entirely verified:
	 *   CHARG: 1 if uncharging, 0 if charging
	 *   USB: 1 if not connected, 0 if connected
	 *   BATTERY: battery capacity from 000 (empty) to 100 (full)
	 */

	lx = (ext[0] & 0xff) | ((ext[1] & 0x0f) << 8);
	rx = (ext[2] & 0xff) | ((ext[3] & 0x0f) << 8);
	ly = (ext[4] & 0xff) | ((ext[5] & 0x0f) << 8);
	ry = (ext[6] & 0xff) | ((ext[7] & 0x0f) << 8);

	/* zero-point offsets */
	lx -= 0x800;
	ly = 0x800 - ly;
	rx -= 0x800;
	ry = 0x800 - ry;

	/* Trivial automatic calibration. We don't know any calibration data
	 * in the EEPROM so we must use the first report to calibrate the
	 * null-position of the analog sticks. Users can retrigger calibration
	 * via sysfs, or set it explicitly. If data is off more than abs(500),
	 * we skip calibration as the sticks are likely to be moved already. */
	if (!(wdata->state.flags & WIIPROTO_FLAG_PRO_CALIB_DONE)) {
		wdata->state.flags |= WIIPROTO_FLAG_PRO_CALIB_DONE;
		if (abs(lx) < 500)
			wdata->state.calib_pro_sticks[0] = -lx;
		if (abs(ly) < 500)
			wdata->state.calib_pro_sticks[1] = -ly;
		if (abs(rx) < 500)
			wdata->state.calib_pro_sticks[2] = -rx;
		if (abs(ry) < 500)
			wdata->state.calib_pro_sticks[3] = -ry;
	}

	/* apply calibration data */
	lx += wdata->state.calib_pro_sticks[0];
	ly += wdata->state.calib_pro_sticks[1];
	rx += wdata->state.calib_pro_sticks[2];
	ry += wdata->state.calib_pro_sticks[3];

	input_report_abs(wdata->extension.input, ABS_X, lx);
	input_report_abs(wdata->extension.input, ABS_Y, ly);
	input_report_abs(wdata->extension.input, ABS_RX, rx);
	input_report_abs(wdata->extension.input, ABS_RY, ry);

	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_RIGHT],
			 !(ext[8] & 0x80));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_DOWN],
			 !(ext[8] & 0x40));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_TL],
			 !(ext[8] & 0x20));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_MINUS],
			 !(ext[8] & 0x10));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_HOME],
			 !(ext[8] & 0x08));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_PLUS],
			 !(ext[8] & 0x04));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_TR],
			 !(ext[8] & 0x02));

	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_ZL],
			 !(ext[9] & 0x80));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_B],
			 !(ext[9] & 0x40));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_Y],
			 !(ext[9] & 0x20));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_A],
			 !(ext[9] & 0x10));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_X],
			 !(ext[9] & 0x08));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_ZR],
			 !(ext[9] & 0x04));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_LEFT],
			 !(ext[9] & 0x02));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_UP],
			 !(ext[9] & 0x01));

	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_THUMBL],
			 !(ext[10] & 0x02));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_THUMBR],
			 !(ext[10] & 0x01));

	input_sync(wdata->extension.input);
}