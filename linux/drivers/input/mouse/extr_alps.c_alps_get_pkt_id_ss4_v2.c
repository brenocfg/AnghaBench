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
typedef  enum SS4_PACKET_ID { ____Placeholder_SS4_PACKET_ID } SS4_PACKET_ID ;

/* Variables and functions */
 int /*<<< orphan*/  SS4_IS_IDLE_V2 (unsigned char*) ; 
 int SS4_PACKET_ID_IDLE ; 
 int SS4_PACKET_ID_MULTI ; 
 int SS4_PACKET_ID_ONE ; 
 int SS4_PACKET_ID_STICK ; 
 int SS4_PACKET_ID_TWO ; 

__attribute__((used)) static enum SS4_PACKET_ID alps_get_pkt_id_ss4_v2(unsigned char *byte)
{
	enum SS4_PACKET_ID pkt_id = SS4_PACKET_ID_IDLE;

	switch (byte[3] & 0x30) {
	case 0x00:
		if (SS4_IS_IDLE_V2(byte)) {
			pkt_id = SS4_PACKET_ID_IDLE;
		} else {
			pkt_id = SS4_PACKET_ID_ONE;
		}
		break;
	case 0x10:
		/* two-finger finger positions */
		pkt_id = SS4_PACKET_ID_TWO;
		break;
	case 0x20:
		/* stick pointer */
		pkt_id = SS4_PACKET_ID_STICK;
		break;
	case 0x30:
		/* third and fourth finger positions */
		pkt_id = SS4_PACKET_ID_MULTI;
		break;
	}

	return pkt_id;
}