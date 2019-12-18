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
struct psmouse {int dummy; } ;

/* Variables and functions */
#define  PACKET_UNKNOWN 131 
#define  PACKET_V4_HEAD 130 
#define  PACKET_V4_MOTION 129 
#define  PACKET_V4_STATUS 128 
 int /*<<< orphan*/  process_packet_head_v4 (struct psmouse*) ; 
 int /*<<< orphan*/  process_packet_motion_v4 (struct psmouse*) ; 
 int /*<<< orphan*/  process_packet_status_v4 (struct psmouse*) ; 

__attribute__((used)) static void elantech_report_absolute_v4(struct psmouse *psmouse,
					int packet_type)
{
	switch (packet_type) {
	case PACKET_V4_STATUS:
		process_packet_status_v4(psmouse);
		break;

	case PACKET_V4_HEAD:
		process_packet_head_v4(psmouse);
		break;

	case PACKET_V4_MOTION:
		process_packet_motion_v4(psmouse);
		break;

	case PACKET_UNKNOWN:
	default:
		/* impossible to get here */
		break;
	}
}