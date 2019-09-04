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
struct psmouse {int pktcnt; unsigned char* packet; struct cytp_data* private; } ;
struct cytp_data {int pkt_size; int mode; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int CYTP_BIT_ABS_NO_PRESSURE ; 
 int CYTP_BIT_ABS_REL_MASK ; 
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int cypress_get_finger_count (unsigned char) ; 
 int /*<<< orphan*/  cypress_process_packet (struct psmouse*,int) ; 
 int /*<<< orphan*/  cypress_set_packet_size (struct psmouse*,int) ; 

__attribute__((used)) static psmouse_ret_t cypress_validate_byte(struct psmouse *psmouse)
{
	int contact_cnt;
	int index = psmouse->pktcnt - 1;
	unsigned char *packet = psmouse->packet;
	struct cytp_data *cytp = psmouse->private;

	if (index < 0 || index > cytp->pkt_size)
		return PSMOUSE_BAD_DATA;

	if (index == 0 && (packet[0] & 0xfc) == 0) {
		/* call packet process for reporting finger leave. */
		cypress_process_packet(psmouse, 1);
		return PSMOUSE_FULL_PACKET;
	}

	/*
	 * Perform validation (and adjust packet size) based only on the
	 * first byte; allow all further bytes through.
	 */
	if (index != 0)
		return PSMOUSE_GOOD_DATA;

	/*
	 * If absolute/relative mode bit has not been set yet, just pass
	 * the byte through.
	 */
	if ((cytp->mode & CYTP_BIT_ABS_REL_MASK) == 0)
		return PSMOUSE_GOOD_DATA;

	if ((packet[0] & 0x08) == 0x08)
		return PSMOUSE_BAD_DATA;

	contact_cnt = cypress_get_finger_count(packet[0]);
	if (cytp->mode & CYTP_BIT_ABS_NO_PRESSURE)
		cypress_set_packet_size(psmouse, contact_cnt == 2 ? 7 : 4);
	else
		cypress_set_packet_size(psmouse, contact_cnt == 2 ? 8 : 5);

	return PSMOUSE_GOOD_DATA;
}