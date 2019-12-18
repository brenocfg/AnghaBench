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
struct input_mt_pos {unsigned char x; unsigned char y; } ;

/* Variables and functions */
#define  V7_PACKET_ID_MULTI 130 
#define  V7_PACKET_ID_NEW 129 
#define  V7_PACKET_ID_TWO 128 

__attribute__((used)) static void alps_get_finger_coordinate_v7(struct input_mt_pos *mt,
					  unsigned char *pkt,
					  unsigned char pkt_id)
{
	mt[0].x = ((pkt[2] & 0x80) << 4);
	mt[0].x |= ((pkt[2] & 0x3F) << 5);
	mt[0].x |= ((pkt[3] & 0x30) >> 1);
	mt[0].x |= (pkt[3] & 0x07);
	mt[0].y = (pkt[1] << 3) | (pkt[0] & 0x07);

	mt[1].x = ((pkt[3] & 0x80) << 4);
	mt[1].x |= ((pkt[4] & 0x80) << 3);
	mt[1].x |= ((pkt[4] & 0x3F) << 4);
	mt[1].y = ((pkt[5] & 0x80) << 3);
	mt[1].y |= ((pkt[5] & 0x3F) << 4);

	switch (pkt_id) {
	case V7_PACKET_ID_TWO:
		mt[1].x &= ~0x000F;
		mt[1].y |= 0x000F;
		/* Detect false-postive touches where x & y report max value */
		if (mt[1].y == 0x7ff && mt[1].x == 0xff0) {
			mt[1].x = 0;
			/* y gets set to 0 at the end of this function */
		}
		break;

	case V7_PACKET_ID_MULTI:
		mt[1].x &= ~0x003F;
		mt[1].y &= ~0x0020;
		mt[1].y |= ((pkt[4] & 0x02) << 4);
		mt[1].y |= 0x001F;
		break;

	case V7_PACKET_ID_NEW:
		mt[1].x &= ~0x003F;
		mt[1].x |= (pkt[0] & 0x20);
		mt[1].y |= 0x000F;
		break;
	}

	mt[0].y = 0x7FF - mt[0].y;
	mt[1].y = 0x7FF - mt[1].y;
}