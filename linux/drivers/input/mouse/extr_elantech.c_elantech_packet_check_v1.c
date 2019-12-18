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
struct psmouse {unsigned char* packet; struct elantech_data* private; } ;
struct TYPE_2__ {int fw_version; } ;
struct elantech_data {unsigned char* parity; TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static int elantech_packet_check_v1(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;
	unsigned char *packet = psmouse->packet;
	unsigned char p1, p2, p3;

	/* Parity bits are placed differently */
	if (etd->info.fw_version < 0x020000) {
		/* byte 0:  D   U  p1  p2   1  p3   R   L */
		p1 = (packet[0] & 0x20) >> 5;
		p2 = (packet[0] & 0x10) >> 4;
	} else {
		/* byte 0: n1  n0  p2  p1   1  p3   R   L */
		p1 = (packet[0] & 0x10) >> 4;
		p2 = (packet[0] & 0x20) >> 5;
	}

	p3 = (packet[0] & 0x04) >> 2;

	return etd->parity[packet[1]] == p1 &&
	       etd->parity[packet[2]] == p2 &&
	       etd->parity[packet[3]] == p3;
}