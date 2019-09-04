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
struct psmouse {unsigned char* packet; struct input_dev* dev; struct elantech_data* private; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ reports_pressure; } ;
struct elantech_data {TYPE_1__ info; int /*<<< orphan*/  y_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_QUADTAP ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  elantech_report_semi_mt_data (struct input_dev*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,unsigned char) ; 

__attribute__((used)) static void elantech_report_absolute_v2(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;
	struct input_dev *dev = psmouse->dev;
	unsigned char *packet = psmouse->packet;
	unsigned int fingers, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	unsigned int width = 0, pres = 0;

	/* byte 0: n1  n0   .   .   .   .   R   L */
	fingers = (packet[0] & 0xc0) >> 6;

	switch (fingers) {
	case 3:
		/*
		 * Same as one finger, except report of more than 3 fingers:
		 * byte 3:  n4  .   w1  w0   .   .   .   .
		 */
		if (packet[3] & 0x80)
			fingers = 4;
		/* fall through */
	case 1:
		/*
		 * byte 1:  .   .   .   .  x11 x10 x9  x8
		 * byte 2: x7  x6  x5  x4  x4  x2  x1  x0
		 */
		x1 = ((packet[1] & 0x0f) << 8) | packet[2];
		/*
		 * byte 4:  .   .   .   .  y11 y10 y9  y8
		 * byte 5: y7  y6  y5  y4  y3  y2  y1  y0
		 */
		y1 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);

		pres = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
		width = ((packet[0] & 0x30) >> 2) | ((packet[3] & 0x30) >> 4);
		break;

	case 2:
		/*
		 * The coordinate of each finger is reported separately
		 * with a lower resolution for two finger touches:
		 * byte 0:  .   .  ay8 ax8  .   .   .   .
		 * byte 1: ax7 ax6 ax5 ax4 ax3 ax2 ax1 ax0
		 */
		x1 = (((packet[0] & 0x10) << 4) | packet[1]) << 2;
		/* byte 2: ay7 ay6 ay5 ay4 ay3 ay2 ay1 ay0 */
		y1 = etd->y_max -
			((((packet[0] & 0x20) << 3) | packet[2]) << 2);
		/*
		 * byte 3:  .   .  by8 bx8  .   .   .   .
		 * byte 4: bx7 bx6 bx5 bx4 bx3 bx2 bx1 bx0
		 */
		x2 = (((packet[3] & 0x10) << 4) | packet[4]) << 2;
		/* byte 5: by7 by8 by5 by4 by3 by2 by1 by0 */
		y2 = etd->y_max -
			((((packet[3] & 0x20) << 3) | packet[5]) << 2);

		/* Unknown so just report sensible values */
		pres = 127;
		width = 7;
		break;
	}

	input_report_key(dev, BTN_TOUCH, fingers != 0);
	if (fingers != 0) {
		input_report_abs(dev, ABS_X, x1);
		input_report_abs(dev, ABS_Y, y1);
	}
	elantech_report_semi_mt_data(dev, fingers, x1, y1, x2, y2);
	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);
	input_report_key(dev, BTN_TOOL_QUADTAP, fingers == 4);
	psmouse_report_standard_buttons(dev, packet[0]);
	if (etd->info.reports_pressure) {
		input_report_abs(dev, ABS_PRESSURE, pres);
		input_report_abs(dev, ABS_TOOL_WIDTH, width);
	}

	input_sync(dev);
}