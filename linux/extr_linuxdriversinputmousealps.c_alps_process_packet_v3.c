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
struct psmouse {unsigned char* packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  alps_process_touchpad_packet_v3_v5 (struct psmouse*) ; 
 int /*<<< orphan*/  alps_process_trackstick_packet_v3 (struct psmouse*) ; 

__attribute__((used)) static void alps_process_packet_v3(struct psmouse *psmouse)
{
	unsigned char *packet = psmouse->packet;

	/*
	 * v3 protocol packets come in three types, two representing
	 * touchpad data and one representing trackstick data.
	 * Trackstick packets seem to be distinguished by always
	 * having 0x3f in the last byte. This value has never been
	 * observed in the last byte of either of the other types
	 * of packets.
	 */
	if (packet[5] == 0x3f) {
		alps_process_trackstick_packet_v3(psmouse);
		return;
	}

	alps_process_touchpad_packet_v3_v5(psmouse);
}