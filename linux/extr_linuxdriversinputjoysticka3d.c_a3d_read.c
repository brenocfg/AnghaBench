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
struct input_dev {int dummy; } ;
struct a3d {int mode; char* axes; unsigned char buttons; struct input_dev* dev; } ;

/* Variables and functions */
#define  A3D_MODE_A3D 131 
#define  A3D_MODE_OEM 130 
#define  A3D_MODE_PAN 129 
#define  A3D_MODE_PXL 128 
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_HAT1X ; 
 int /*<<< orphan*/  ABS_HAT1Y ; 
 int /*<<< orphan*/  ABS_RUDDER ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_PINKIE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  BTN_THUMB ; 
 int /*<<< orphan*/  BTN_TOP ; 
 int /*<<< orphan*/  BTN_TRIGGER ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void a3d_read(struct a3d *a3d, unsigned char *data)
{
	struct input_dev *dev = a3d->dev;

	switch (a3d->mode) {

		case A3D_MODE_A3D:
		case A3D_MODE_OEM:
		case A3D_MODE_PAN:

			input_report_rel(dev, REL_X, ((data[5] << 6) | (data[6] << 3) | data[ 7]) - ((data[5] & 4) << 7));
			input_report_rel(dev, REL_Y, ((data[8] << 6) | (data[9] << 3) | data[10]) - ((data[8] & 4) << 7));

			input_report_key(dev, BTN_RIGHT,  data[2] & 1);
			input_report_key(dev, BTN_LEFT,   data[3] & 2);
			input_report_key(dev, BTN_MIDDLE, data[3] & 4);

			input_sync(dev);

			a3d->axes[0] = ((signed char)((data[11] << 6) | (data[12] << 3) | (data[13]))) + 128;
			a3d->axes[1] = ((signed char)((data[14] << 6) | (data[15] << 3) | (data[16]))) + 128;
			a3d->axes[2] = ((signed char)((data[17] << 6) | (data[18] << 3) | (data[19]))) + 128;
			a3d->axes[3] = ((signed char)((data[20] << 6) | (data[21] << 3) | (data[22]))) + 128;

			a3d->buttons = ((data[3] << 3) | data[4]) & 0xf;

			break;

		case A3D_MODE_PXL:

			input_report_rel(dev, REL_X, ((data[ 9] << 6) | (data[10] << 3) | data[11]) - ((data[ 9] & 4) << 7));
			input_report_rel(dev, REL_Y, ((data[12] << 6) | (data[13] << 3) | data[14]) - ((data[12] & 4) << 7));

			input_report_key(dev, BTN_RIGHT,  data[2] & 1);
			input_report_key(dev, BTN_LEFT,   data[3] & 2);
			input_report_key(dev, BTN_MIDDLE, data[3] & 4);
			input_report_key(dev, BTN_SIDE,   data[7] & 2);
			input_report_key(dev, BTN_EXTRA,  data[7] & 4);

			input_report_abs(dev, ABS_X,        ((signed char)((data[15] << 6) | (data[16] << 3) | (data[17]))) + 128);
			input_report_abs(dev, ABS_Y,        ((signed char)((data[18] << 6) | (data[19] << 3) | (data[20]))) + 128);
			input_report_abs(dev, ABS_RUDDER,   ((signed char)((data[21] << 6) | (data[22] << 3) | (data[23]))) + 128);
			input_report_abs(dev, ABS_THROTTLE, ((signed char)((data[24] << 6) | (data[25] << 3) | (data[26]))) + 128);

			input_report_abs(dev, ABS_HAT0X, ( data[5]       & 1) - ((data[5] >> 2) & 1));
			input_report_abs(dev, ABS_HAT0Y, ((data[5] >> 1) & 1) - ((data[6] >> 2) & 1));
			input_report_abs(dev, ABS_HAT1X, ((data[4] >> 1) & 1) - ( data[3]       & 1));
			input_report_abs(dev, ABS_HAT1Y, ((data[4] >> 2) & 1) - ( data[4]       & 1));

			input_report_key(dev, BTN_TRIGGER, data[8] & 1);
			input_report_key(dev, BTN_THUMB,   data[8] & 2);
			input_report_key(dev, BTN_TOP,     data[8] & 4);
			input_report_key(dev, BTN_PINKIE,  data[7] & 1);

			input_sync(dev);

			break;
	}
}