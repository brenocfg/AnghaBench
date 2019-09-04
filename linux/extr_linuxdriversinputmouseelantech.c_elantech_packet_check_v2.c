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
struct TYPE_2__ {scalar_t__ reports_pressure; } ;
struct elantech_data {TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static int elantech_packet_check_v2(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;
	unsigned char *packet = psmouse->packet;

	/*
	 * V2 hardware has two flavors. Older ones that do not report pressure,
	 * and newer ones that reports pressure and width. With newer ones, all
	 * packets (1, 2, 3 finger touch) have the same constant bits. With
	 * older ones, 1/3 finger touch packets and 2 finger touch packets
	 * have different constant bits.
	 * With all three cases, if the constant bits are not exactly what I
	 * expected, I consider them invalid.
	 */
	if (etd->info.reports_pressure)
		return (packet[0] & 0x0c) == 0x04 &&
		       (packet[3] & 0x0f) == 0x02;

	if ((packet[0] & 0xc0) == 0x80)
		return (packet[0] & 0x0c) == 0x0c &&
		       (packet[3] & 0x0e) == 0x08;

	return (packet[0] & 0x3c) == 0x3c &&
	       (packet[1] & 0xf0) == 0x00 &&
	       (packet[3] & 0x3e) == 0x38 &&
	       (packet[4] & 0xf0) == 0x00;
}