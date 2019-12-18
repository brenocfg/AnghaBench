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
struct psmouse {unsigned char* packet; struct elantech_data* private; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
struct elantech_data {int /*<<< orphan*/  info; int /*<<< orphan*/  y_max; TYPE_1__* mt; } ;
struct TYPE_2__ {unsigned char x; unsigned int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int PACKET_V3_HEAD ; 
 scalar_t__ elantech_is_buttonpad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elantech_report_semi_mt_data (struct input_dev*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,unsigned char) ; 

__attribute__((used)) static void elantech_report_absolute_v3(struct psmouse *psmouse,
					int packet_type)
{
	struct input_dev *dev = psmouse->dev;
	struct elantech_data *etd = psmouse->private;
	unsigned char *packet = psmouse->packet;
	unsigned int fingers = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	unsigned int width = 0, pres = 0;

	/* byte 0: n1  n0   .   .   .   .   R   L */
	fingers = (packet[0] & 0xc0) >> 6;

	switch (fingers) {
	case 3:
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
		break;

	case 2:
		if (packet_type == PACKET_V3_HEAD) {
			/*
			 * byte 1:   .    .    .    .  ax11 ax10 ax9  ax8
			 * byte 2: ax7  ax6  ax5  ax4  ax3  ax2  ax1  ax0
			 */
			etd->mt[0].x = ((packet[1] & 0x0f) << 8) | packet[2];
			/*
			 * byte 4:   .    .    .    .  ay11 ay10 ay9  ay8
			 * byte 5: ay7  ay6  ay5  ay4  ay3  ay2  ay1  ay0
			 */
			etd->mt[0].y = etd->y_max -
				(((packet[4] & 0x0f) << 8) | packet[5]);
			/*
			 * wait for next packet
			 */
			return;
		}

		/* packet_type == PACKET_V3_TAIL */
		x1 = etd->mt[0].x;
		y1 = etd->mt[0].y;
		x2 = ((packet[1] & 0x0f) << 8) | packet[2];
		y2 = etd->y_max - (((packet[4] & 0x0f) << 8) | packet[5]);
		break;
	}

	pres = (packet[1] & 0xf0) | ((packet[4] & 0xf0) >> 4);
	width = ((packet[0] & 0x30) >> 2) | ((packet[3] & 0x30) >> 4);

	input_report_key(dev, BTN_TOUCH, fingers != 0);
	if (fingers != 0) {
		input_report_abs(dev, ABS_X, x1);
		input_report_abs(dev, ABS_Y, y1);
	}
	elantech_report_semi_mt_data(dev, fingers, x1, y1, x2, y2);
	input_report_key(dev, BTN_TOOL_FINGER, fingers == 1);
	input_report_key(dev, BTN_TOOL_DOUBLETAP, fingers == 2);
	input_report_key(dev, BTN_TOOL_TRIPLETAP, fingers == 3);

	/* For clickpads map both buttons to BTN_LEFT */
	if (elantech_is_buttonpad(&etd->info))
		input_report_key(dev, BTN_LEFT, packet[0] & 0x03);
	else
		psmouse_report_standard_buttons(dev, packet[0]);

	input_report_abs(dev, ABS_PRESSURE, pres);
	input_report_abs(dev, ABS_TOOL_WIDTH, width);

	input_sync(dev);
}