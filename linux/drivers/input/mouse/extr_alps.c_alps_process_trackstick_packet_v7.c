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
struct psmouse {unsigned char* packet; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_data {int flags; struct input_dev* dev2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int ALPS_DUALPOINT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,unsigned char) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 

__attribute__((used)) static void alps_process_trackstick_packet_v7(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	unsigned char *packet = psmouse->packet;
	struct input_dev *dev2 = priv->dev2;
	int x, y, z;

	/* It should be a DualPoint when received trackstick packet */
	if (!(priv->flags & ALPS_DUALPOINT)) {
		psmouse_warn(psmouse,
			     "Rejected trackstick packet from non DualPoint device");
		return;
	}

	x = ((packet[2] & 0xbf)) | ((packet[3] & 0x10) << 2);
	y = (packet[3] & 0x07) | (packet[4] & 0xb8) |
	    ((packet[3] & 0x20) << 1);
	z = (packet[5] & 0x3f) | ((packet[3] & 0x80) >> 1);

	input_report_rel(dev2, REL_X, (char)x);
	input_report_rel(dev2, REL_Y, -((char)y));
	input_report_abs(dev2, ABS_PRESSURE, z);

	psmouse_report_standard_buttons(dev2, packet[1]);

	input_sync(dev2);
}