#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct psmouse {struct alps_data* private; } ;
struct alps_fields {int fingers; unsigned char left; unsigned char right; unsigned char middle; TYPE_1__* mt; } ;
struct alps_data {int flags; } ;
struct TYPE_3__ {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 int ALPS_BUTTONPAD ; 
 unsigned char V7_PACKET_ID_IDLE ; 
 unsigned char V7_PACKET_ID_NEW ; 
 unsigned char V7_PACKET_ID_TWO ; 
 unsigned char V7_PACKET_ID_UNKNOWN ; 
 int /*<<< orphan*/  alps_get_finger_coordinate_v7 (TYPE_1__*,unsigned char*,unsigned char) ; 
 int alps_get_mt_count (TYPE_1__*) ; 
 unsigned char alps_get_packet_id_v7 (unsigned char*) ; 

__attribute__((used)) static int alps_decode_packet_v7(struct alps_fields *f,
				  unsigned char *p,
				  struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	unsigned char pkt_id;

	pkt_id = alps_get_packet_id_v7(p);
	if (pkt_id == V7_PACKET_ID_IDLE)
		return 0;
	if (pkt_id == V7_PACKET_ID_UNKNOWN)
		return -1;
	/*
	 * NEW packets are send to indicate a discontinuity in the finger
	 * coordinate reporting. Specifically a finger may have moved from
	 * slot 0 to 1 or vice versa. INPUT_MT_TRACK takes care of this for
	 * us.
	 *
	 * NEW packets have 3 problems:
	 * 1) They do not contain middle / right button info (on non clickpads)
	 *    this can be worked around by preserving the old button state
	 * 2) They do not contain an accurate fingercount, and they are
	 *    typically send when the number of fingers changes. We cannot use
	 *    the old finger count as that may mismatch with the amount of
	 *    touch coordinates we've available in the NEW packet
	 * 3) Their x data for the second touch is inaccurate leading to
	 *    a possible jump of the x coordinate by 16 units when the first
	 *    non NEW packet comes in
	 * Since problems 2 & 3 cannot be worked around, just ignore them.
	 */
	if (pkt_id == V7_PACKET_ID_NEW)
		return 1;

	alps_get_finger_coordinate_v7(f->mt, p, pkt_id);

	if (pkt_id == V7_PACKET_ID_TWO)
		f->fingers = alps_get_mt_count(f->mt);
	else /* pkt_id == V7_PACKET_ID_MULTI */
		f->fingers = 3 + (p[5] & 0x03);

	f->left = (p[0] & 0x80) >> 7;
	if (priv->flags & ALPS_BUTTONPAD) {
		if (p[0] & 0x20)
			f->fingers++;
		if (p[0] & 0x10)
			f->fingers++;
	} else {
		f->right = (p[0] & 0x20) >> 5;
		f->middle = (p[0] & 0x10) >> 4;
	}

	/* Sometimes a single touch is reported in mt[1] rather then mt[0] */
	if (f->fingers == 1 && f->mt[0].x == 0 && f->mt[0].y == 0) {
		f->mt[0].x = f->mt[1].x;
		f->mt[0].y = f->mt[1].y;
		f->mt[1].x = 0;
		f->mt[1].y = 0;
	}

	return 0;
}