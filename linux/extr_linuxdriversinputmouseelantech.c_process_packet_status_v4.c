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
 int ETP_MAX_FINGERS ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  elantech_input_sync_v4 (struct psmouse*) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 

__attribute__((used)) static void process_packet_status_v4(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	unsigned char *packet = psmouse->packet;
	unsigned fingers;
	int i;

	/* notify finger state change */
	fingers = packet[1] & 0x1f;
	for (i = 0; i < ETP_MAX_FINGERS; i++) {
		if ((fingers & (1 << i)) == 0) {
			input_mt_slot(dev, i);
			input_mt_report_slot_state(dev, MT_TOOL_FINGER, false);
		}
	}

	elantech_input_sync_v4(psmouse);
}