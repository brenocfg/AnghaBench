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
struct psmouse {int* packet; int pktcnt; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  BTN_TASK ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (struct input_dev*,int) ; 
 int /*<<< orphan*/  psmouse_report_standard_packet (struct input_dev*,int*) ; 
 int /*<<< orphan*/  sign_extend32 (int,int) ; 

__attribute__((used)) static psmouse_ret_t ps2pp_process_byte(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	u8 *packet = psmouse->packet;

	if (psmouse->pktcnt < 3)
		return PSMOUSE_GOOD_DATA;

/*
 * Full packet accumulated, process it
 */

	if ((packet[0] & 0x48) == 0x48 && (packet[1] & 0x02) == 0x02) {

		/* Logitech extended packet */
		switch ((packet[1] >> 4) | (packet[0] & 0x30)) {

		case 0x0d: /* Mouse extra info */

			input_report_rel(dev,
				packet[2] & 0x80 ? REL_HWHEEL : REL_WHEEL,
				-sign_extend32(packet[2], 3));
			input_report_key(dev, BTN_SIDE,  packet[2] & BIT(4));
			input_report_key(dev, BTN_EXTRA, packet[2] & BIT(5));

			break;

		case 0x0e: /* buttons 4, 5, 6, 7, 8, 9, 10 info */

			input_report_key(dev, BTN_SIDE,    packet[2] & BIT(0));
			input_report_key(dev, BTN_EXTRA,   packet[2] & BIT(1));
			input_report_key(dev, BTN_TASK,    packet[2] & BIT(2));
			input_report_key(dev, BTN_BACK,    packet[2] & BIT(3));
			input_report_key(dev, BTN_FORWARD, packet[2] & BIT(4));

			break;

		case 0x0f: /* TouchPad extra info */

			input_report_rel(dev,
				packet[2] & 0x08 ? REL_HWHEEL : REL_WHEEL,
				-sign_extend32(packet[2] >> 4, 3));
			packet[0] = packet[2] | BIT(3);
			break;

		default:
			psmouse_dbg(psmouse,
				    "Received PS2++ packet #%x, but don't know how to handle.\n",
				    (packet[1] >> 4) | (packet[0] & 0x30));
			break;
		}

		psmouse_report_standard_buttons(dev, packet[0]);

	} else {
		/* Standard PS/2 motion data */
		psmouse_report_standard_packet(dev, packet);
	}

	input_sync(dev);

	return PSMOUSE_FULL_PACKET;

}