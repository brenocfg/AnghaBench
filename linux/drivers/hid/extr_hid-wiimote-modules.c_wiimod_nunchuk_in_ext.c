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
struct TYPE_3__ {int flags; } ;
struct wiimote_data {TYPE_2__ extension; TYPE_1__ state; } ;
typedef  int __u8 ;
typedef  int __s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_RZ ; 
 size_t WIIMOD_NUNCHUK_KEY_C ; 
 size_t WIIMOD_NUNCHUK_KEY_Z ; 
 int WIIPROTO_FLAG_MP_ACTIVE ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wiimod_nunchuk_map ; 

__attribute__((used)) static void wiimod_nunchuk_in_ext(struct wiimote_data *wdata, const __u8 *ext)
{
	__s16 x, y, z, bx, by;

	/*   Byte |   8    7 |  6    5 |  4    3 |  2 |  1  |
	 *   -----+----------+---------+---------+----+-----+
	 *    1   |              Button X <7:0>             |
	 *    2   |              Button Y <7:0>             |
	 *   -----+----------+---------+---------+----+-----+
	 *    3   |               Speed X <9:2>             |
	 *    4   |               Speed Y <9:2>             |
	 *    5   |               Speed Z <9:2>             |
	 *   -----+----------+---------+---------+----+-----+
	 *    6   | Z <1:0>  | Y <1:0> | X <1:0> | BC | BZ  |
	 *   -----+----------+---------+---------+----+-----+
	 * Button X/Y is the analog stick. Speed X, Y and Z are the
	 * accelerometer data in the same format as the wiimote's accelerometer.
	 * The 6th byte contains the LSBs of the accelerometer data.
	 * BC and BZ are the C and Z buttons: 0 means pressed
	 *
	 * If reported interleaved with motionp, then the layout changes. The
	 * 5th and 6th byte changes to:
	 *   -----+-----------------------------------+-----+
	 *    5   |            Speed Z <9:3>          | EXT |
	 *   -----+--------+-----+-----+----+----+----+-----+
	 *    6   |Z <2:1> |Y <1>|X <1>| BC | BZ | 0  |  0  |
	 *   -----+--------+-----+-----+----+----+----+-----+
	 * All three accelerometer values lose their LSB. The other data is
	 * still available but slightly moved.
	 *
	 * Center data for button values is 128. Center value for accelerometer
	 * values it 512 / 0x200
	 */

	bx = ext[0];
	by = ext[1];
	bx -= 128;
	by -= 128;

	x = ext[2] << 2;
	y = ext[3] << 2;
	z = ext[4] << 2;

	if (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) {
		x |= (ext[5] >> 3) & 0x02;
		y |= (ext[5] >> 4) & 0x02;
		z &= ~0x4;
		z |= (ext[5] >> 5) & 0x06;
	} else {
		x |= (ext[5] >> 2) & 0x03;
		y |= (ext[5] >> 4) & 0x03;
		z |= (ext[5] >> 6) & 0x03;
	}

	x -= 0x200;
	y -= 0x200;
	z -= 0x200;

	input_report_abs(wdata->extension.input, ABS_HAT0X, bx);
	input_report_abs(wdata->extension.input, ABS_HAT0Y, by);

	input_report_abs(wdata->extension.input, ABS_RX, x);
	input_report_abs(wdata->extension.input, ABS_RY, y);
	input_report_abs(wdata->extension.input, ABS_RZ, z);

	if (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) {
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_Z],
			!(ext[5] & 0x04));
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_C],
			!(ext[5] & 0x08));
	} else {
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_Z],
			!(ext[5] & 0x01));
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_C],
			!(ext[5] & 0x02));
	}

	input_sync(wdata->extension.input);
}