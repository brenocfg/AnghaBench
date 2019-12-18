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
struct psmouse {unsigned char* packet; struct input_dev* dev; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_data {scalar_t__ proto_version; int flags; int prev_fin; struct input_dev* dev2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int ALPS_DUALPOINT ; 
 int ALPS_FOUR_BUTTONS ; 
 int ALPS_FW_BK_1 ; 
 int ALPS_FW_BK_2 ; 
 scalar_t__ ALPS_PROTO_V1 ; 
 int ALPS_STICK_BITS ; 
 int ALPS_WHEEL ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_3 ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  alps_report_buttons (struct input_dev*,struct input_dev*,int,int,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void alps_process_packet_v1_v2(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	unsigned char *packet = psmouse->packet;
	struct input_dev *dev = psmouse->dev;
	struct input_dev *dev2 = priv->dev2;
	int x, y, z, ges, fin, left, right, middle;
	int back = 0, forward = 0;

	if (priv->proto_version == ALPS_PROTO_V1) {
		left = packet[2] & 0x10;
		right = packet[2] & 0x08;
		middle = 0;
		x = packet[1] | ((packet[0] & 0x07) << 7);
		y = packet[4] | ((packet[3] & 0x07) << 7);
		z = packet[5];
	} else {
		left = packet[3] & 1;
		right = packet[3] & 2;
		middle = packet[3] & 4;
		x = packet[1] | ((packet[2] & 0x78) << (7 - 3));
		y = packet[4] | ((packet[3] & 0x70) << (7 - 4));
		z = packet[5];
	}

	if (priv->flags & ALPS_FW_BK_1) {
		back = packet[0] & 0x10;
		forward = packet[2] & 4;
	}

	if (priv->flags & ALPS_FW_BK_2) {
		back = packet[3] & 4;
		forward = packet[2] & 4;
		if ((middle = forward && back))
			forward = back = 0;
	}

	ges = packet[2] & 1;
	fin = packet[2] & 2;

	if ((priv->flags & ALPS_DUALPOINT) && z == 127) {
		input_report_rel(dev2, REL_X,  (x > 383 ? (x - 768) : x));
		input_report_rel(dev2, REL_Y, -(y > 255 ? (y - 512) : y));

		alps_report_buttons(dev2, dev, left, right, middle);

		input_sync(dev2);
		return;
	}

	/* Some models have separate stick button bits */
	if (priv->flags & ALPS_STICK_BITS) {
		left |= packet[0] & 1;
		right |= packet[0] & 2;
		middle |= packet[0] & 4;
	}

	alps_report_buttons(dev, dev2, left, right, middle);

	/* Convert hardware tap to a reasonable Z value */
	if (ges && !fin)
		z = 40;

	/*
	 * A "tap and drag" operation is reported by the hardware as a transition
	 * from (!fin && ges) to (fin && ges). This should be translated to the
	 * sequence Z>0, Z==0, Z>0, so the Z==0 event has to be generated manually.
	 */
	if (ges && fin && !priv->prev_fin) {
		input_report_abs(dev, ABS_X, x);
		input_report_abs(dev, ABS_Y, y);
		input_report_abs(dev, ABS_PRESSURE, 0);
		input_report_key(dev, BTN_TOOL_FINGER, 0);
		input_sync(dev);
	}
	priv->prev_fin = fin;

	if (z > 30)
		input_report_key(dev, BTN_TOUCH, 1);
	if (z < 25)
		input_report_key(dev, BTN_TOUCH, 0);

	if (z > 0) {
		input_report_abs(dev, ABS_X, x);
		input_report_abs(dev, ABS_Y, y);
	}

	input_report_abs(dev, ABS_PRESSURE, z);
	input_report_key(dev, BTN_TOOL_FINGER, z > 0);

	if (priv->flags & ALPS_WHEEL)
		input_report_rel(dev, REL_WHEEL, ((packet[2] << 1) & 0x08) - ((packet[0] >> 4) & 0x07));

	if (priv->flags & (ALPS_FW_BK_1 | ALPS_FW_BK_2)) {
		input_report_key(dev, BTN_FORWARD, forward);
		input_report_key(dev, BTN_BACK, back);
	}

	if (priv->flags & ALPS_FOUR_BUTTONS) {
		input_report_key(dev, BTN_0, packet[2] & 4);
		input_report_key(dev, BTN_1, packet[0] & 0x10);
		input_report_key(dev, BTN_2, packet[3] & 4);
		input_report_key(dev, BTN_3, packet[0] & 0x20);
	}

	input_sync(dev);
}