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
struct TYPE_2__ {int fw_version; int* samples; scalar_t__ crc_enabled; } ;
struct elantech_data {TYPE_1__ info; scalar_t__ tp_dev; } ;

/* Variables and functions */
 int PACKET_TRACKPOINT ; 
 int PACKET_UNKNOWN ; 
 int PACKET_V4_HEAD ; 
 int PACKET_V4_MOTION ; 
 int PACKET_V4_STATUS ; 

__attribute__((used)) static int elantech_packet_check_v4(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;
	unsigned char *packet = psmouse->packet;
	unsigned char packet_type = packet[3] & 0x03;
	unsigned int ic_version;
	bool sanity_check;

	if (etd->tp_dev && (packet[3] & 0x0f) == 0x06)
		return PACKET_TRACKPOINT;

	/* This represents the version of IC body. */
	ic_version = (etd->info.fw_version & 0x0f0000) >> 16;

	/*
	 * Sanity check based on the constant bits of a packet.
	 * The constant bits change depending on the value of
	 * the hardware flag 'crc_enabled' and the version of
	 * the IC body, but are the same for every packet,
	 * regardless of the type.
	 */
	if (etd->info.crc_enabled)
		sanity_check = ((packet[3] & 0x08) == 0x00);
	else if (ic_version == 7 && etd->info.samples[1] == 0x2A)
		sanity_check = ((packet[3] & 0x1c) == 0x10);
	else
		sanity_check = ((packet[0] & 0x08) == 0x00 &&
				(packet[3] & 0x1c) == 0x10);

	if (!sanity_check)
		return PACKET_UNKNOWN;

	switch (packet_type) {
	case 0:
		return PACKET_V4_STATUS;

	case 1:
		return PACKET_V4_HEAD;

	case 2:
		return PACKET_V4_MOTION;
	}

	return PACKET_UNKNOWN;
}