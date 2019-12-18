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
struct dc_info_packet {unsigned char* sb; int valid; scalar_t__ hb3; scalar_t__ hb2; scalar_t__ hb1; scalar_t__ hb0; } ;

/* Variables and functions */

__attribute__((used)) static void build_vrr_infopacket_checksum(unsigned int *payload_size,
		struct dc_info_packet *infopacket)
{
	/* Calculate checksum */
	unsigned int idx = 0;
	unsigned char checksum = 0;

	checksum += infopacket->hb0;
	checksum += infopacket->hb1;
	checksum += infopacket->hb2;
	checksum += infopacket->hb3;

	for (idx = 1; idx <= *payload_size; idx++)
		checksum += infopacket->sb[idx];

	/* PB0 = Checksum (one byte complement) */
	infopacket->sb[0] = (unsigned char)(0x100 - checksum);

	infopacket->valid = true;
}