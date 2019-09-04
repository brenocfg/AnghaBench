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
typedef  int u32 ;
typedef  int u16 ;
struct bu21029_ts_data {int x_plate_ohms; int /*<<< orphan*/  in_dev; int /*<<< orphan*/  prop; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALE_12BIT ; 
 int input_abs_get_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touchscreen_report_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void bu21029_touch_report(struct bu21029_ts_data *bu21029, const u8 *buf)
{
	u16 x, y, z1, z2;
	u32 rz;
	s32 max_pressure = input_abs_get_max(bu21029->in_dev, ABS_PRESSURE);

	/*
	 * compose upper 8 and lower 4 bits into a 12bit value:
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |            ByteH              |            ByteL              |
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |b07|b06|b05|b04|b03|b02|b01|b00|b07|b06|b05|b04|b03|b02|b01|b00|
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |v11|v10|v09|v08|v07|v06|v05|v04|v03|v02|v01|v00| 0 | 0 | 0 | 0 |
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 */
	x  = (buf[0] << 4) | (buf[1] >> 4);
	y  = (buf[2] << 4) | (buf[3] >> 4);
	z1 = (buf[4] << 4) | (buf[5] >> 4);
	z2 = (buf[6] << 4) | (buf[7] >> 4);

	if (z1 && z2) {
		/*
		 * calculate Rz (pressure resistance value) by equation:
		 * Rz = Rx * (x/Q) * ((z2/z1) - 1), where
		 * Rx is x-plate resistance,
		 * Q  is the touch screen resolution (8bit = 256, 12bit = 4096)
		 * x, z1, z2 are the measured positions.
		 */
		rz  = z2 - z1;
		rz *= x;
		rz *= bu21029->x_plate_ohms;
		rz /= z1;
		rz  = DIV_ROUND_CLOSEST(rz, SCALE_12BIT);
		if (rz <= max_pressure) {
			touchscreen_report_pos(bu21029->in_dev, &bu21029->prop,
					       x, y, false);
			input_report_abs(bu21029->in_dev, ABS_PRESSURE,
					 max_pressure - rz);
			input_report_key(bu21029->in_dev, BTN_TOUCH, 1);
			input_sync(bu21029->in_dev);
		}
	}
}