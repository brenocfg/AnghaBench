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
struct psmouse {unsigned char* packet; int pktcnt; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  vmmouse_report_events (struct psmouse*) ; 

__attribute__((used)) static psmouse_ret_t vmmouse_process_byte(struct psmouse *psmouse)
{
	unsigned char *packet = psmouse->packet;

	switch (psmouse->pktcnt) {
	case 1:
		return (packet[0] & 0x8) == 0x8 ?
			PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;

	case 2:
		return PSMOUSE_GOOD_DATA;

	default:
		return vmmouse_report_events(psmouse);
	}
}