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
struct wiimote_data {int /*<<< orphan*/  mp; } ;
typedef  int __u8 ;
typedef  int __u16 ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wiimod_mp_in_mp(struct wiimote_data *wdata, const __u8 *ext)
{
	__s32 x, y, z;

	/*        |   8    7    6    5    4    3 |  2  |  1  |
	 *   -----+------------------------------+-----+-----+
	 *    1   |               Yaw Speed <7:0>            |
	 *    2   |              Roll Speed <7:0>            |
	 *    3   |             Pitch Speed <7:0>            |
	 *   -----+------------------------------+-----+-----+
	 *    4   |       Yaw Speed <13:8>       | Yaw |Pitch|
	 *   -----+------------------------------+-----+-----+
	 *    5   |      Roll Speed <13:8>       |Roll | Ext |
	 *   -----+------------------------------+-----+-----+
	 *    6   |     Pitch Speed <13:8>       |  1  |  0  |
	 *   -----+------------------------------+-----+-----+
	 * The single bits Yaw, Roll, Pitch in the lower right corner specify
	 * whether the wiimote is rotating fast (0) or slow (1). Speed for slow
	 * roation is 8192/440 units / deg/s and for fast rotation 8192/2000
	 * units / deg/s. To get a linear scale for fast rotation we multiply
	 * by 2000/440 = ~4.5454 and scale both fast and slow by 9 to match the
	 * previous scale reported by this driver.
	 * This leaves a linear scale with 8192*9/440 (~167.564) units / deg/s.
	 * If the wiimote is not rotating the sensor reports 2^13 = 8192.
	 * Ext specifies whether an extension is connected to the motionp.
	 * which is parsed by wiimote-core.
	 */

	x = ext[0];
	y = ext[1];
	z = ext[2];

	x |= (((__u16)ext[3]) << 6) & 0xff00;
	y |= (((__u16)ext[4]) << 6) & 0xff00;
	z |= (((__u16)ext[5]) << 6) & 0xff00;

	x -= 8192;
	y -= 8192;
	z -= 8192;

	if (!(ext[3] & 0x02))
		x = (x * 2000 * 9) / 440;
	else
		x *= 9;
	if (!(ext[4] & 0x02))
		y = (y * 2000 * 9) / 440;
	else
		y *= 9;
	if (!(ext[3] & 0x01))
		z = (z * 2000 * 9) / 440;
	else
		z *= 9;

	input_report_abs(wdata->mp, ABS_RX, x);
	input_report_abs(wdata->mp, ABS_RY, y);
	input_report_abs(wdata->mp, ABS_RZ, z);
	input_sync(wdata->mp);
}