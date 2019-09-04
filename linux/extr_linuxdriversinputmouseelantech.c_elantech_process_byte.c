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
struct psmouse {scalar_t__ pktcnt; scalar_t__ pktsize; struct elantech_data* private; } ;
struct TYPE_2__ {int debug; int hw_version; int /*<<< orphan*/  paritycheck; } ;
struct elantech_data {TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
#define  PACKET_DEBOUNCE 130 
#define  PACKET_TRACKPOINT 129 
#define  PACKET_UNKNOWN 128 
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  elantech_debounce_check_v2 (struct psmouse*) ; 
 int /*<<< orphan*/  elantech_packet_check_v1 (struct psmouse*) ; 
 int /*<<< orphan*/  elantech_packet_check_v2 (struct psmouse*) ; 
 int elantech_packet_check_v3 (struct psmouse*) ; 
 int elantech_packet_check_v4 (struct psmouse*) ; 
 int /*<<< orphan*/  elantech_packet_dump (struct psmouse*) ; 
 int /*<<< orphan*/  elantech_report_absolute_v1 (struct psmouse*) ; 
 int /*<<< orphan*/  elantech_report_absolute_v2 (struct psmouse*) ; 
 int /*<<< orphan*/  elantech_report_absolute_v3 (struct psmouse*,int) ; 
 int /*<<< orphan*/  elantech_report_absolute_v4 (struct psmouse*,int) ; 
 int /*<<< orphan*/  elantech_report_trackpoint (struct psmouse*,int) ; 

__attribute__((used)) static psmouse_ret_t elantech_process_byte(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;
	int packet_type;

	if (psmouse->pktcnt < psmouse->pktsize)
		return PSMOUSE_GOOD_DATA;

	if (etd->info.debug > 1)
		elantech_packet_dump(psmouse);

	switch (etd->info.hw_version) {
	case 1:
		if (etd->info.paritycheck && !elantech_packet_check_v1(psmouse))
			return PSMOUSE_BAD_DATA;

		elantech_report_absolute_v1(psmouse);
		break;

	case 2:
		/* ignore debounce */
		if (elantech_debounce_check_v2(psmouse))
			return PSMOUSE_FULL_PACKET;

		if (etd->info.paritycheck && !elantech_packet_check_v2(psmouse))
			return PSMOUSE_BAD_DATA;

		elantech_report_absolute_v2(psmouse);
		break;

	case 3:
		packet_type = elantech_packet_check_v3(psmouse);
		switch (packet_type) {
		case PACKET_UNKNOWN:
			return PSMOUSE_BAD_DATA;

		case PACKET_DEBOUNCE:
			/* ignore debounce */
			break;

		case PACKET_TRACKPOINT:
			elantech_report_trackpoint(psmouse, packet_type);
			break;

		default:
			elantech_report_absolute_v3(psmouse, packet_type);
			break;
		}

		break;

	case 4:
		packet_type = elantech_packet_check_v4(psmouse);
		switch (packet_type) {
		case PACKET_UNKNOWN:
			return PSMOUSE_BAD_DATA;

		case PACKET_TRACKPOINT:
			elantech_report_trackpoint(psmouse, packet_type);
			break;

		default:
			elantech_report_absolute_v4(psmouse, packet_type);
			break;
		}

		break;
	}

	return PSMOUSE_FULL_PACKET;
}