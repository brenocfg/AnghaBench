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
struct psmouse {unsigned char* packet; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 scalar_t__ hgpk_discard_decay_hack (struct psmouse*,int,int) ; 
 int /*<<< orphan*/  hgpk_spewing_hack (struct psmouse*,int,int,int,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,...) ; 
 scalar_t__ tpdebug ; 

__attribute__((used)) static void hgpk_process_simple_packet(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	unsigned char *packet = psmouse->packet;
	int left = packet[0] & 1;
	int right = (packet[0] >> 1) & 1;
	int x = packet[1] - ((packet[0] << 4) & 0x100);
	int y = ((packet[0] << 3) & 0x100) - packet[2];

	if (packet[0] & 0xc0)
		psmouse_dbg(psmouse,
			    "overflow -- 0x%02x 0x%02x 0x%02x\n",
			    packet[0], packet[1], packet[2]);

	if (hgpk_discard_decay_hack(psmouse, x, y)) {
		if (tpdebug)
			psmouse_dbg(psmouse, "discarding\n");
		return;
	}

	hgpk_spewing_hack(psmouse, left, right, x, y);

	if (tpdebug)
		psmouse_dbg(psmouse, "l=%d r=%d x=%d y=%d\n",
			    left, right, x, y);

	input_report_key(dev, BTN_LEFT, left);
	input_report_key(dev, BTN_RIGHT, right);

	input_report_rel(dev, REL_X, x);
	input_report_rel(dev, REL_Y, y);

	input_sync(dev);
}